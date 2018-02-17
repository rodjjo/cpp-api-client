/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "asio-client.h"

namespace apiclient {

ApiClient::ApiClient(const std::string& client) {
}

ApiClient::~ApiClient() {
}

Json::Value ApiClient::get(const std::string& query_string,
        int timeout = 0, const ApiHeaders *headers = NULL) {
}

void get(const std::string& query_string,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) {
}

Json::Value post(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void post(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Json::Value put(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void put(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Json::Value del(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void del(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Json::Value patch(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void patch(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);


} // namespace apiclient
