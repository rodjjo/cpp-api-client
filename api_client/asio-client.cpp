/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/asio-client.h"


namespace apiclient {

ApiClient::ApiClient(const std::string& base_url) : base_url_(base_url) {
  url_fragments_t fragments = apiclient::decompose_url(base_url);
  if (!fragments.valid) {
    throw ApiException((std::string("Invalid url: ") + base_url).c_str());
  }
  secure_ = fragments.secure;
  host_ = fragments.host;
  port_ = fragments.port;

}

ApiClient::~ApiClient() {
}

Json::Value ApiClient::get(const std::string& query_string,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::post(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::put(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::del(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::patch(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

}  // namespace apiclient
