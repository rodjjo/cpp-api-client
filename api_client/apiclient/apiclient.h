/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_APICLIENT_APICLIENT_H_
#define API_CLIENT_APICLIENT_APICLIENT_H_

#include <jsoncpp/json/json.h>
#include <functional>
#include <utility>
#include <map>
#include <string>
#include <memory>

namespace apiclient {


typedef std::map<std::string, std::string> ApiHeaders;

class Response {
 public:
    Response();
    virtual ~Response();

 public:
    int status;
    int error;
    ApiHeaders headers;
    Json::Value body;
};


typedef std::function<void(const Response&,
                           const ApiHeaders&)> ResponseHandler;


class ClientBase {
 public:
    virtual ~ClientBase();
    virtual Response get(const std::string& query_string,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Response post(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Response put(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Response del(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual Response patch(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
};

class ClientBuilderBase {
 public:
    virtual ~ClientBuilderBase();
    virtual std::shared_ptr<ClientBase> client(const std::string& base_url) = 0;
};

std::shared_ptr<ClientBuilderBase> builder();

}  // namespace apiclient

#endif  // API_CLIENT_APICLIENT_APICLIENT_H_

