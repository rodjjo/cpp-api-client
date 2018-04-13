/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/api-exception.h"
#include "api_client/protocol-client.h"
#include "api_client/api-response.h"

namespace apiclient {

ProtocolClient::ProtocolClient(
    std::shared_ptr<ClientIo> client_io,
    const std::string& host,
    int port
): resolver_(
    new Resolver(&client_io->io_service, host, port)
) {
    client_io_ = client_io;
}

ProtocolClient::~ProtocolClient() {
}

void ProtocolClient::resolve(ResolverHandler handler) {
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

const std::string& ProtocolClient::get_host() {
    return resolver_->get_host();
}

boost::asio::ip::tcp::resolver::iterator&
        ProtocolClient::get_resolver_iterator() {
    return *resolver_->get();
}

boost::asio::io_service* ProtocolClient::get_io_service() {
    return &client_io_->io_service;
}

void ProtocolClient::delivery_response(
    std::stringstream& data,
    ResponseHandler response_handler) {
    ApiHeaders headers;
    std::string body;
    int status = parse_http_stream(data, &body, &headers);

    response_handler(Response(body, headers, status));
}

void ProtocolClient::request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout) {
    resolve([this, response_handler, message, timeout] (
            const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator iter) {
        if (err) {
            response_handler(apiclient::Response(err.value()));
            return;
        }

        request(iter, message, response_handler, timeout);
    });
}

}  // namespace apiclient
