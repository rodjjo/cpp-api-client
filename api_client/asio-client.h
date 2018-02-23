/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_ASIO_CLIENT_H_
#define API_CLIENT_ASIO_CLIENT_H_

#include <memory>
#include <string>
#include "api_client/apiclient/apiclient.h"
#include "api_client/asio-resolver.h"


namespace apiclient {

class Client: public ClientBase {
 public:
    explicit Client(const std::string& base_url);
    virtual ~Client();
    Response get(const std::string& query_string,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Response post(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Response put(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Response del(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);
    Response patch(const std::string& query_string,
        const Json::Value& body,
        int timeout = 0, const ApiHeaders *headers = NULL);
    void patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);

 private:
    std::string base_url_;
    std::string host_;
    int port_;
    bool secure_;
    std::shared_ptr<Resolver> resolver_;
};

}  // namespace apiclient

#endif  // API_CLIENT_ASIO_CLIENT_H_
