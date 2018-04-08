/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/http-client.h"


namespace apiclient {

HTTPClient::HTTPClient(std::shared_ptr<ClientIo> client_io,
    location_t location) :
        ProtocolClientBase(client_io, location.host, location.port) {
}

HTTPClient::~HTTPClient() {
}

void HTTPClient::process_response(
    std::shared_ptr<boost::asio::ip::tcp::socket> socket,
    std::shared_ptr<boost::asio::streambuf> buffer,
    std::shared_ptr<std::stringstream> data,
    ResponseHandler response_handler
) {
    boost::asio::async_read(
        *socket.get(),
        *buffer.get(),
        boost::asio::transfer_at_least(1), [
            this,
            socket,
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
                socket->shutdown(
                        boost::asio::ip::tcp::socket::shutdown_both);
                socket->close();
                delivery_response(*data.get(), response_handler);
            } else if (err) {
                response_handler(apiclient::Response(err.value()));
            } else {
                if (bytestransfered) {
                    (*data.get()) << &(*buffer.get());
                }

                process_response(
                    socket, buffer, data, response_handler);
            }
        });
}

void HTTPClient::make_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    resolve([this, response_handler, message] (
            const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator iter) {
        if (err) {
            response_handler(apiclient::Response(err.value()));
            return;
        }

        std::shared_ptr<boost::asio::ip::tcp::socket> socket(
            new boost::asio::ip::tcp::socket(get_io_service()));

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

                        std::shared_ptr<boost::asio::streambuf> buffer(
                            new boost::asio::streambuf());
                        std::shared_ptr<std::stringstream> data(
                            new std::stringstream());

                        process_response(
                            socket, buffer, data, response_handler);
                    });
            });
    });
}

}  // namespace apiclient
