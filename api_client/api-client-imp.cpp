/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/api-exception.h"
#include "api_client/utils.h"
#include "api_client/https-client.h"
#include "api_client/http-client.h"
#include "api_client/api-client-imp.h"

namespace apiclient {

ClientImp::ClientImp(std::shared_ptr<ClientIo> client_io,
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

ClientImp::~ClientImp() {
}

const std::string& ClientImp::get_host() {
    return client_->get_host();
}

std::shared_ptr<boost::asio::streambuf> ClientImp::get_message(
    http_method_t method,
    const std::string& query_string,
    const Json::Value* body,
    const ApiHeaders *headers
) {
    auto message = std::shared_ptr<boost::asio::streambuf>(
        new boost::asio::streambuf());

    compose_request(method, get_host(), query_string, headers, body, message.get());

    return message;
}

void ClientImp::get(
    const std::string& query_string,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_get, query_string, NULL, headers));
    client_->request(message, response_handler, timeout);
}

void ClientImp::post(
    const std::string& query_string,
    const Json::Value& body,
    ResponseHandler response_handler,
    int timeout,
    const ApiHeaders *headers
) {
    auto message(get_message(http_post, query_string, &body, headers));
    client_->request(message, response_handler, timeout);
}

void ClientImp::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_put, query_string, &body, headers));
    client_->request(message, response_handler, timeout);
}

void ClientImp::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_delete, query_string, &body, headers));
    client_->request(message, response_handler, timeout);
}

void ClientImp::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
    auto message(get_message(http_patch, query_string, &body, headers));
    client_->request(message, response_handler, timeout);
}

}  // namespace apiclient
