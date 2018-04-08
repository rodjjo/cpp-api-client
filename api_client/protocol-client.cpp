/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/protocol-client.h"
#include "api_client/https-client.h"
#include "api_client/http-client.h"
#include "api_client/api-response.h"

namespace apiclient {


ClientIo::ClientIo(unsigned char num_threads) {
    if (num_threads < 1) {
        num_threads = 1;
    }
    work_.reset(new boost::asio::io_service::work(io_service));
    for (unsigned char c = 0; c < num_threads; ++c) {
        threads_.push_back(
            std::shared_ptr<boost::thread> (
                new boost::thread([this] () {
                    io_service.reset();
                    io_service.run();
                })));
    }
}

ClientIo::~ClientIo() {
    work_.reset();
    io_service.stop();
    for (auto it = threads_.begin(); it != threads_.end(); ++it) {
        (*it)->join();
    }
}


ProtocolClientBase::ProtocolClientBase(
    std::shared_ptr<ClientIo> client_io,
    const std::string& host,
    int port
): resolver_(
    new Resolver(&client_io->io_service, host, port)
) {
    client_io_ = client_io;
}

ProtocolClientBase::~ProtocolClientBase() {
}

void ProtocolClientBase::resolve(ResolverHandler handler) {
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

const std::string& ProtocolClientBase::get_host() {
    return resolver_->get_host();
}

boost::asio::ip::tcp::resolver::iterator& ProtocolClientBase::get_resolver_iterator() {
    return *resolver_->get();
}

boost::asio::io_service& ProtocolClientBase::get_io_service() {
    return client_io_->io_service;
}


void ProtocolClientBase::delivery_response(
    std::stringstream& data,
    ResponseHandler response_handler,
    DeliveryHandler handler) {
    ApiHeaders headers;
    std::string body;
    int status = parse_http_stream(data, &body, &headers);

    response_handler(Response(body, headers, status));

    handler();
}



Client::Client(std::shared_ptr<ClientIo> client_io,
    const std::string& base_url, asio_ssl::verify_mode ssl_verify_mode) {
  location_t fragments = apiclient::decompose_url(base_url);
  if (!fragments.valid) {
    throw ApiException((std::string("Invalid url: ") + base_url).c_str());
  }

  if (fragments.secure) {
    client_.reset(new HTTPSClient(client_io, fragments, ssl_verify_mode));
  } else {
    client_.reset(new HTTPClient(client_io, fragments));
  }
}

Client::~Client() {
}

const std::string& Client::get_host() {
    return client_->get_host();
}

std::shared_ptr<boost::asio::streambuf> Client::get_message(
    http_method_t method,
    const std::string& query_string,
    const Json::Value* body,
    const ApiHeaders *headers
) {
    auto message = std::shared_ptr<boost::asio::streambuf>(new boost::asio::streambuf());

    compose_request(method, get_host(), query_string, headers, body, message.get());

    return message;
}

void Client::get(
    const std::string& query_string,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_get, query_string, NULL, headers));
    client_->make_request(message, response_handler, timeout);
}

void Client::post(
    const std::string& query_string,
    const Json::Value& body,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_post, query_string, &body, headers));
    client_->make_request(message, response_handler, timeout);
}

void Client::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_put, query_string, &body, headers));
    client_->make_request(message, response_handler, timeout);
}

void Client::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_delete, query_string, &body, headers));
    client_->make_request(message, response_handler, timeout);
}

void Client::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_patch, query_string, &body, headers));
    client_->make_request(message, response_handler, timeout);
}


}  // namespace apiclient
