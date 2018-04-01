/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_ASIO_CLIENT_H_
#define API_CLIENT_ASIO_CLIENT_H_

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
    std::shared_ptr<boost::thread> thread_;
};


typedef std::function<void(boost::system::error_code error,
    boost::asio::ip::tcp::resolver::iterator)> resolver_function;


typedef std::shared_ptr<
            boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
        >  sslsocket_t;

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> streamsocket_t;

typedef std::function<void (
        sslsocket_t ssl_socket
    )> BuildSocketHandler;

typedef std::function<void(
        const boost::system::error_code& err,
        boost::asio::ip::tcp::resolver::iterator iterator
    )>  ConnectHandler;

typedef std::function<void()> DeliveryHandler;

namespace asio_ssl = boost::asio::ssl;

class Client: public ClientBase {
 public:
    explicit Client(std::shared_ptr<ClientIo> client_io,
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

 protected:
    void resolve(resolver_function handler);
    bool verify_certificate(bool preverified, asio_ssl::verify_context& ctx);

    std::shared_ptr<boost::asio::streambuf> get_message(
        http_method_t method,
        const std::string& query_string,
        const Json::Value* body,
        const ApiHeaders *headers = NULL);

    void https_request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout);

    void http_request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout);

    void build_ssl_socket(BuildSocketHandler handler);
    void ssl_connect(streamsocket_t *socket, ConnectHandler handler);
    void process_ssl_request(
        sslsocket_t ssl_socket,
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler);
    void process_ssl_response(
        sslsocket_t ssl_socket,
        ResponseHandler response_handler
    );

    void delivery_response(std::stringstream& data, ResponseHandler response_handler, DeliveryHandler handler);

    void request(std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout = 0);
 private:
    std::string base_url_;
    std::string host_;
    int port_;
    asio_ssl::verify_mode ssl_verify_mode_;
    std::shared_ptr<boost::asio::ssl::context> ssl_context_;
    std::shared_ptr<Resolver> resolver_;
    std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient

#endif  // API_CLIENT_ASIO_CLIENT_H_
