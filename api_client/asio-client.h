/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_ASIO_CLIENT_H_
#define API_CLIENT_ASIO_CLIENT_H_

#include <memory>
#include <functional>
#include <string>
#include <thread>

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#endif

#include "api_client/apiclient/apiclient.h"
#include "api_client/asio-resolver.h"
#include "api_client/api-request.h"

namespace apiclient {

class ClientIo {
 public:
    ClientIo();
    virtual ~ClientIo();

    boost::asio::io_service io_service;

 private:
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::shared_ptr<std::thread> thread_;
};


typedef std::function<void(boost::system::error_code error,
    boost::asio::ip::tcp::resolver::iterator)> resolver_function;

class Client: public ClientBase {
 public:
    explicit Client(std::shared_ptr<ClientIo> client_io,
        const std::string& base_url);
    virtual ~Client();
    void get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;

 protected:
    void resolve(resolver_function handler);
    void request(http_method_t method,
        const std::string& query_string,
        const Json::Value* body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL);

 private:
    std::string base_url_;
    std::string host_;
    int port_;
    std::shared_ptr<boost::asio::ssl::context> ssl_context_;
    std::shared_ptr<Resolver> resolver_;
    std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient

#endif  // API_CLIENT_ASIO_CLIENT_H_
