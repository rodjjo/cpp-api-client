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
    explicit Response(int error);
    Response(const std::string& data,
        const ApiHeaders & headers, int status);
    virtual ~Response();
    int get_status() const;
    int get_error() const;
    bool has_error() const;
    bool is_json() const;
    const ApiHeaders& get_headers() const;
    const Json::Value& get_body() const;
    const std::string& get_data()  const;
 private:
    int status_;
    int error_;
    bool is_json_;
    bool has_error_;
    ApiHeaders headers_;
    std::string data_;
    Json::Value body_;
};

typedef std::function<void(const Response&)> ResponseHandler;

class ClientBase {
 public:
    virtual ~ClientBase();
    virtual void get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) = 0;
    virtual void del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
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

std::shared_ptr<ClientBuilderBase> builder(unsigned char num_threads);

}  // namespace apiclient

#endif  // API_CLIENT_APICLIENT_APICLIENT_H_

