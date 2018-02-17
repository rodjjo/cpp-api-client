/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_APICLIENT_APICLIENT_H_
#define API_CLIENT_APICLIENT_APICLIENT_H_

#include <json/json.h>
#include <utility>
#include <list>
#include <string>
#include <memory>


namespace apiclient {

typedef std::pair<std::string, std::string> ApiHeader;
typedef std::list<ApiHeader> ApiHeaders;

class ResponseHandler {
 public:
    virtual ~ResponseHandler();
    virtual void api_response(const Json::Value& response,
        const ApiHeaders& headers) = 0;
};

class ApiBase {
 public:
    virtual ~ApiBase();
    virtual Json::Value get(const std::string& query_string,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void get(const std::string& query_string,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Json::Value post(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void post(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Json::Value put(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void put(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Json::Value del(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void del(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Json::Value patch(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void patch(const std::string& query_string,
        const Json::Value& body,
        std::shared_ptr<ResponseHandler> response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
};

std::shared_ptr<ApiBase> build(const std::string& base_url);

}  // namespace apiclient

#endif  // API_CLIENT_APICLIENT_APICLIENT_H_

