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
        const std::string& base_url) : base_url_(base_url) {
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

void Client::get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    request(http_get, query_string, NULL, response_handler, timeout, headers);
}

void Client::post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    request(http_post, query_string, &body, response_handler, timeout, headers);
}

void Client::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    request(http_put, query_string, &body, response_handler, timeout, headers);
}

void Client::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    request(http_delete, query_string, &body, response_handler, timeout,
            headers);
}

void Client::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    request(http_patch, query_string, &body, response_handler, timeout,
            headers);
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

void Client::request(http_method_t method,
        const std::string& query_string,
        const Json::Value *body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    std::shared_ptr<boost::asio::streambuf> message(
        new boost::asio::streambuf());
    compose_request(method, host_, query_string, headers, message.get());

    if (ssl_context_) {
    } else {
    }
}

}  // namespace apiclient
