/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/asio-client.h"


namespace apiclient {


ClientIo::ClientIo() {
    work_.reset(new boost::asio::io_service::work(io_service));
    thread_.reset(new boost::thread([this] () {
        io_service.reset();
        io_service.run();
    }));
}

ClientIo::~ClientIo() {
    work_.reset();
    io_service.stop();
    thread_->join();
}


Client::Client(std::shared_ptr<ClientIo> client_io,
    const std::string& base_url, asio_ssl::verify_mode ssl_verify_mode) :
        base_url_(base_url), ssl_verify_mode_(ssl_verify_mode) {
  url_fragments_t fragments = apiclient::decompose_url(base_url);
  if (!fragments.valid) {
    throw ApiException((std::string("Invalid url: ") + base_url).c_str());
  }
  host_ = fragments.host;
  port_ = fragments.port;
  client_io_ = client_io;
  resolver_.reset(new Resolver(&client_io_->io_service, host_, port_));
  if (fragments.secure) {
    ssl_context_.reset(new boost::asio::ssl::context(
                    boost::asio::ssl::context::tlsv12));
    ssl_context_->set_default_verify_paths();
  }
}

Client::~Client() {
}

void Client::get(
    const std::string& query_string,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_get, query_string, NULL, headers));
    request(message, response_handler, timeout);
}

void Client::post(
    const std::string& query_string,
    const Json::Value& body,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_post, query_string, &body, headers));
    request(message, response_handler, timeout);
}

void Client::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_put, query_string, &body, headers));
    request(message, response_handler, timeout);
}

void Client::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_delete, query_string, &body, headers));
    request(message, response_handler, timeout);
}

void Client::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_patch, query_string, &body, headers));
    request(message, response_handler, timeout);
}

void Client::resolve(resolver_function handler) {
    if (resolver_->get()) {
        auto success = boost::system::errc::success;
        handler(boost::system::errc::make_error_code(success),
            *resolver_->get());
    } else {
        resolver_->resolve([handler](const boost::system::error_code& error,
            boost::asio::ip::tcp::resolver::iterator iterator) {
        handler(error, iterator);
    });
    }
}

void Client::request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    if (ssl_context_) {
        https_request(message, response_handler, timeout);
    } else {
        http_request(message, response_handler, timeout);
    }
}

std::shared_ptr<boost::asio::streambuf> Client::get_message(
    http_method_t method,
    const std::string& query_string,
    const Json::Value* body,
    const ApiHeaders *headers
) {
    auto message = std::shared_ptr<boost::asio::streambuf>(new boost::asio::streambuf());

    compose_request(method, host_, query_string, headers, body, message.get());

    return message;
}


bool Client::verify_certificate(bool preverified, asio_ssl::verify_context& ctx) {
    return preverified;
}

void Client::http_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {


}



void Client::build_ssl_socket(BuildSocketHandler handler) {
    boost::asio::ssl::context & context = *(ssl_context_.get());

    auto ssl_socket = std::shared_ptr<
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> > (
        new boost::asio::ssl::stream<boost::asio::ip::tcp::socket> (
            client_io_->io_service, context
        )
    );

    auto socket = static_cast<boost::asio::ssl::stream<
        boost::asio::ip::tcp::socket>* >(ssl_socket.get());

    socket->set_verify_mode(ssl_verify_mode_);
    SSL_set_tlsext_host_name(socket->native_handle(), host_.c_str());

    handler(ssl_socket);
}


void Client::ssl_connect(streamsocket_t *socket, ConnectHandler handler) {
    boost::asio::async_connect(socket->lowest_layer(), *resolver_->get(), handler);
}

void Client::delivery_response(
    std::stringstream& data,
    ResponseHandler response_handler,
    DeliveryHandler handler) {

    response_handler(Response()); // TODO(RODRIGO): write response

    handler();
}

void Client::process_ssl_response(
    sslsocket_t ssl_socket,
    ResponseHandler response_handler
) {
    std::function<void(const boost::system::error_code&, std::size_t)> handler_read;

    std::shared_ptr<boost::asio::streambuf> buffer(new boost::asio::streambuf());
    std::shared_ptr<std::stringstream> data(new std::stringstream());

    handler_read = [
        this,
        ssl_socket,
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
                ssl_socket
            ] () {
                auto tcp_socket = static_cast<streamsocket_t *>(ssl_socket.get());
                tcp_socket->shutdown();
				tcp_socket->lowest_layer().close();
            });
        } else if (err) {
            response_handler(apiclient::Response().with_error(err.value()));
        } else {
            if (bytestransfered) {
                (*data.get()) << &(*buffer.get());
            }
/*
            boost::asio::async_read(
                *static_cast<streamsocket_t *>(ssl_socket.get()),
                *buffer.get(),
                boost::asio::transfer_at_least(1),
                handler_read
            );
*/
        }
    };

    handler_read(boost::system::errc::make_error_code(boost::system::errc::success), 0);
}

void Client::process_ssl_request(
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
                response_handler(apiclient::Response().with_error(err.value()));
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
                        response_handler(apiclient::Response().with_error(err.value()));
                        return;
                    }

                    process_ssl_response(ssl_socket, response_handler);
                }
            );
        }
    );
}

void Client::https_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    build_ssl_socket([
        this,
        message,
        response_handler,
        timeout
    ] (sslsocket_t ssl_socket) {
        ssl_connect(
            static_cast<streamsocket_t *>(ssl_socket.get()),
            [
                this,
                ssl_socket,
                message,
                response_handler,
                timeout
            ] (const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator iterator)
            {
                if (err) {
                    response_handler(apiclient::Response().with_error(err.value()));
                    return;
                }

                 process_ssl_request(
                    ssl_socket,
                    message,
                    response_handler
                );
            }
        );
    });
}

}  // namespace apiclient
