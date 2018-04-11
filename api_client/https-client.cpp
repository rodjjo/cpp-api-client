/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/https-client.h"


namespace apiclient {

HTTPSClient::HTTPSClient(std::shared_ptr<ClientIo> client_io,
        location_t location,
        asio_ssl::verify_mode ssl_verify_mode
) : HTTPClient(client_io, location) {
    ssl_verify_mode_ = ssl_verify_mode;
    ssl_context_.reset(
        new boost::asio::ssl::context(boost::asio::ssl::context::tlsv12));
    ssl_context_->set_default_verify_paths();
}

HTTPSClient::~HTTPSClient() {
}

void HTTPSClient::connect(
    boost::asio::ip::tcp::resolver::iterator iter,
    unsigned int timeout,
    ConnectHandler handler
) {
    std::shared_ptr<ApiSocket> api_socket(
        new ApiSocket(
            get_io_service(),
            ssl_context_.get(),
            ssl_verify_mode_,
            get_host().c_str(),
            timeout));

    boost::asio::async_connect(
        api_socket->get_secure_socket()->lowest_layer(),
        iter, [handler, api_socket] (
            const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator resolver
        ) {
            if (err) {
                handler(err, api_socket);
                return;
            }
            api_socket->get_secure_socket()->async_handshake(
                asio_ssl::stream_base::client,
            [
                handler, api_socket
            ] (const boost::system::error_code& err) {
                handler(err, api_socket);
            });
        });
}

bool HTTPSClient::verify_certificate(bool preverified,
        asio_ssl::verify_context& ctx) {
    return preverified;
}

}  // namespace apiclient
