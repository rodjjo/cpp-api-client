/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/asio-client.h"


namespace apiclient {

Client::Client(const std::string& base_url) : base_url_(base_url) {
  url_fragments_t fragments = apiclient::decompose_url(base_url);
  if (!fragments.valid) {
    throw ApiException((std::string("Invalid url: ") + base_url).c_str());
  }
  secure_ = fragments.secure;
  host_ = fragments.host;
  port_ = fragments.port;
  // resolver_.reset(new Resolver(...));
}

Client::~Client() {
}

Response Client::get(const std::string& query_string,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::post(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::put(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::del(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::patch(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

}  // namespace apiclient
