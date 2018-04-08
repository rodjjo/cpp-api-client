/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/https-client.h"


namespace apiclient {

HTTPSClient::HTTPSClient(std::shared_ptr<ClientIo> client_io,
        url_fragments_t url_fragments,
        asio_ssl::verify_mode ssl_verify_mode) : ProtocolClientBase(client_io, url_fragments.host, url_fragments.port) {
    ssl_verify_mode_ = ssl_verify_mode;
    ssl_context_.reset(
        new boost::asio::ssl::context(boost::asio::ssl::context::tlsv12)
    );
    ssl_context_->set_default_verify_paths();
}

HTTPSClient::~HTTPSClient() {
}

void HTTPSClient::make_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    auto handle_build_socket = [this, message, response_handler, timeout] (
        sslsocket_t ssl_socket
    ) {
        auto handle_connect = [this, ssl_socket, message, response_handler, timeout] (
            const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator iterator
        ) {
            if (err) {
                response_handler(apiclient::Response(err.value()));
                return;
            }
            process_request(ssl_socket, message, response_handler);
        };

        boost::asio::async_connect(
            static_cast<streamsocket_t *>(ssl_socket.get())->lowest_layer(),
            get_resolver_iterator(),
            handle_connect
        );
    };

    build_ssl_socket(handle_build_socket);
}

bool HTTPSClient::verify_certificate(bool preverified, asio_ssl::verify_context& ctx) {
    return preverified;
}

void HTTPSClient::build_ssl_socket(BuildSocketHandler handler) {
    boost::asio::ssl::context & context = *(ssl_context_.get());

    auto ssl_socket = std::shared_ptr<
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> > (
        new boost::asio::ssl::stream<boost::asio::ip::tcp::socket> (
            get_io_service(), context
        )
    );

    auto socket = static_cast<boost::asio::ssl::stream<
        boost::asio::ip::tcp::socket>* >(ssl_socket.get());

    socket->set_verify_mode(ssl_verify_mode_);
    SSL_set_tlsext_host_name(socket->native_handle(), get_host().c_str());

    handler(ssl_socket);
}

void HTTPSClient::process_response(
    sslsocket_t ssl_socket,
    ResponseHandler response_handler
) {
    std::function<void(const boost::system::error_code&, std::size_t)> read_handler;

    std::shared_ptr<boost::asio::streambuf> buffer(new boost::asio::streambuf());
    std::shared_ptr<std::stringstream> data(new std::stringstream());

    read_handler = [
        this,
        ssl_socket,
        &read_handler,
        buffer,
        data,
        response_handler
    ] (const boost::system::error_code& err, std::size_t bytestransfered) {
        if (
             err.value() == boost::asio::error::eof  || (
                err.category() == boost::asio::error::get_ssl_category() &&
                err.value() == ERROR_VALUE_SSL_SHORT_READ
            )
        ) {
            delivery_response(*data.get(), response_handler, [
                ssl_socket
            ] () {
                auto tcp_socket = static_cast<streamsocket_t *>(ssl_socket.get());
                tcp_socket->shutdown();
				tcp_socket->lowest_layer().close();
            });
        } else if (err) {
            response_handler(apiclient::Response(err.value()));
        } else {
            if (bytestransfered) {
                (*data.get()) << &(*buffer.get());
            }
            boost::asio::async_read(
                *static_cast<streamsocket_t *>(ssl_socket.get()),
                *buffer.get(),
                boost::asio::transfer_at_least(1),
                read_handler
            );
        }
    };

    read_handler(boost::system::errc::make_error_code(boost::system::errc::success), 0);
}

void HTTPSClient::process_request(
    sslsocket_t ssl_socket,
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler
) {
    static_cast<streamsocket_t *>(ssl_socket.get())->async_handshake(
        asio_ssl::stream_base::client,
        [
            this,
            ssl_socket,
            message,
            response_handler
        ] (const boost::system::error_code& err) {
            if (err) {
                response_handler(apiclient::Response(err.value()));
                return;
            }

            boost::asio::async_write(
                *static_cast<streamsocket_t *>(ssl_socket.get()),
                *message.get(), [
                    this,
                    ssl_socket,
                    response_handler
                ] (
                    const boost::system::error_code& err, std::size_t bytestransfered
                ) {
                    if (err) {
                        response_handler(apiclient::Response(err.value()));
                        return;
                    }

                    process_response(ssl_socket, response_handler);
                }
            );
        }
    );
}

}  // namespace apiclient
