/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_PROTOCOL_CLIENT_H_
#define API_CLIENT_PROTOCOL_CLIENT_H_

#include <memory>
#include <functional>
#include <string>
#include <boost/thread.hpp>

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#define ERROR_VALUE_SSL_SHORT_READ ERR_PACK(ERR_LIB_SSL, 0, SSL_R_SHORT_READ)
#endif

#include "api_client/apiclient/apiclient.h"
#include "api_client/location-resolver.h"
#include "api_client/api-request.h"

namespace apiclient {

class ClientIo {
 public:
    ClientIo();
    virtual ~ClientIo();

    boost::asio::io_service io_service;

 private:
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::shared_ptr<boost::thread> thread_;
};


typedef std::function<void(boost::system::error_code error,
    boost::asio::ip::tcp::resolver::iterator)> resolver_function;

typedef std::function<void(
        const boost::system::error_code& err,
        boost::asio::ip::tcp::resolver::iterator iterator
    )>  ConnectHandler;

typedef std::function<void()> DeliveryHandler;


class ProtocolClientBase {
  public:
      ProtocolClientBase(std::shared_ptr<ClientIo> client_io, const std::string& host, int port);

    virtual ~ProtocolClientBase();
    virtual void make_request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout) = 0;
    void resolve(resolver_function handler);
    const std::string& get_host();
    boost::asio::ip::tcp::resolver::iterator& get_resolver_iterator();
    boost::asio::io_service& get_io_service();
  private:
    std::shared_ptr<Resolver> resolver_;
    std::shared_ptr<ClientIo> client_io_;

};

namespace asio_ssl = boost::asio::ssl;

class Client: public ClientBase {
 public:
    Client(std::shared_ptr<ClientIo> client_io,
        const std::string& base_url,
        asio_ssl::verify_mode ssl_verify_mode = asio_ssl::verify_none);
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
 private:
    const std::string& get_host();
    std::shared_ptr<boost::asio::streambuf> get_message(
        http_method_t method,
        const std::string& query_string,
        const Json::Value* body,
        const ApiHeaders *headers = NULL);

    std::shared_ptr<ProtocolClientBase> client_;
};

}  // namespace apiclient

#endif  // API_CLIENT_PROTOCOL_CLIENT_H_
