/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "asio-client.h"

namespace apiclient {

ApiClient::ApiClient(const std::string& base_url) : base_url_(base_url) {
}

ApiClient::~ApiClient() {
}

Json::Value ApiClient::get(const std::string& query_string,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::get(const std::string& query_string,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::post(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::post(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::put(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::put(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::del(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::del(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout, const ApiHeaders *headers) {
}

Json::Value ApiClient::patch(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Json::Value();
}

void ApiClient::patch(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout, const ApiHeaders *headers) {
}

}  // namespace apiclient
