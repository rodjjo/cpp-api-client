/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/http-client.h"


namespace apiclient {

HTTPClient::HTTPClient(std::shared_ptr<ClientIo> client_io,
    location_t location) :
        ProtocolClient(client_io, location.host, location.port) {
}

HTTPClient::~HTTPClient() {
}

void HTTPClient::retrive_response(
    std::shared_ptr<ApiSocket> api_socket,
    std::shared_ptr<boost::asio::streambuf> buffer,
    std::shared_ptr<std::stringstream> data,
    ResponseHandler response_handler
) {
    auto read_handler = [
            this,
            api_socket,
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
                api_socket->finish();
                delivery_response(*data.get(), response_handler);
            } else if (err) {
                response_handler(apiclient::Response(err.value()));
            } else {
                if (bytestransfered) {
                    (*data.get()) << &(*buffer.get());
                }

                retrive_response(
                    api_socket, buffer, data, response_handler);
            }
        };

    if (api_socket->is_secure()) {
        boost::asio::async_read(
            *api_socket->get_secure_socket(),
            *buffer.get(),
            boost::asio::transfer_at_least(1),
            read_handler);
    } else {
        boost::asio::async_read(
            *api_socket->get_socket(),
            *buffer.get(),
            boost::asio::transfer_at_least(1),
            read_handler);
    }
}

void HTTPClient::connect(
    boost::asio::ip::tcp::resolver::iterator iter,
    unsigned int timeout,
    ConnectHandler handler
) {
    std::shared_ptr<ApiSocket> api_socket(
        new ApiSocket(get_io_service(), timeout));

    auto async_conn_handler = [handler, api_socket] (
        const boost::system::error_code& err,
        boost::asio::ip::tcp::resolver::iterator resolver
    ) {
        handler(err, api_socket);
    };

    if (api_socket->is_secure()) {
        boost::asio::async_connect(
            api_socket->get_secure_socket()->lowest_layer(),
            iter,
            async_conn_handler);
    } else {
        boost::asio::async_connect(
            *api_socket->get_socket(), iter, async_conn_handler);
    }
}

void HTTPClient::send_request(
    std::shared_ptr<ApiSocket> api_socket,
    std::shared_ptr<boost::asio::streambuf> message,
    SendRequestHandler send_handler
) {
    auto write_handler = [api_socket, send_handler] (
        const boost::system::error_code& err,
        std::size_t bytestransfered
    ) {
        if (err) {
            send_handler(err);
            return;
        }

        send_handler(boost::system::errc::make_error_code(
            boost::system::errc::success));
    };

    if (api_socket->is_secure()) {
        boost::asio::async_write(
            *api_socket->get_secure_socket(),
            *message.get(),
            write_handler);
    } else {
        boost::asio::async_write(
            *api_socket->get_socket(), *message.get(), write_handler);
    }
}

void HTTPClient::request(
    boost::asio::ip::tcp::resolver::iterator iter,
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {
    connect(iter, timeout, [this, response_handler, message] (
        const boost::system::error_code& err,
        std::shared_ptr<ApiSocket> api_socket
    ) {
        if (err) {
            response_handler(Response(err.value()));
            return;
        }

        send_request(api_socket,  message, [
            this, api_socket, response_handler
        ] (const boost::system::error_code& err) {
            if (err) {
                response_handler(Response(err.value()));
                return;
            }

            std::shared_ptr<boost::asio::streambuf> buffer(
                new boost::asio::streambuf());
            std::shared_ptr<std::stringstream> data(
                new std::stringstream());

            retrive_response(
                api_socket, buffer, data, response_handler);
        });
    });
}

}  // namespace apiclient
