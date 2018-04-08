/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/http-client.h"


namespace apiclient {

HTTPClient::HTTPClient(std::shared_ptr<ClientIo> client_io,
    url_fragments_t url_fragments) :
        ProtocolClientBase(client_io, url_fragments.host, url_fragments.port) {
}

HTTPClient::~HTTPClient() {
}

void HTTPClient::process_response(
    std::shared_ptr<boost::asio::ip::tcp::socket> socket, ResponseHandler response_handler
) {
    std::function<void(const boost::system::error_code&, std::size_t)> handler_read;

    std::shared_ptr<boost::asio::streambuf> buffer(new boost::asio::streambuf());
    std::shared_ptr<std::stringstream> data(new std::stringstream());

    handler_read = [
        this,
        socket,
        &handler_read,
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
                socket
            ] () {
                socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				socket->close();
            });
        } else if (err) {
            response_handler(apiclient::Response(err.value()));
        } else {
            if (bytestransfered) {
                (*data.get()) << &(*buffer.get());
            }
/*
            boost::asio::async_read(
                *static_cast<streamsocket_t *>(socket.get()),
                *buffer.get(),
                boost::asio::transfer_at_least(1),
                handler_read
            );
*/
        }
    };

    handler_read(boost::system::errc::make_error_code(boost::system::errc::success), 0);
}

void HTTPClient::make_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    std::shared_ptr<boost::asio::ip::tcp::socket> socket(
        new boost::asio::ip::tcp::socket(get_io_service())
    );

    boost::asio::async_connect(
        *socket.get(),
        get_resolver_iterator(),
        [this, socket, message, response_handler] (
            const boost::system::error_code& err,
             boost::asio::ip::tcp::resolver::iterator resolver
        ) {
            if (err) {
                response_handler(apiclient::Response(err.value()));
                return;
            }

            boost::asio::async_write(
                *socket.get(),
                *message.get(),
                [this, socket, response_handler] (
                    const boost::system::error_code& err,
                    std::size_t bytestransfered
                ) {
                    if (err) {
                        response_handler(apiclient::Response(err.value()));
                        return;
                    }

                    process_response(socket, response_handler);
                }
			);
        }
    );
}

}  // namespace apiclient
