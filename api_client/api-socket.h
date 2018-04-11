/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_SOCKET_H_
#define API_CLIENT_API_SOCKET_H_

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#endif

#include <boost/noncopyable.hpp>


namespace apiclient {

class ApiSocket : public boost::noncopyable {
 public:
    ApiSocket(boost::asio::io_service *io_service, unsigned int timeout);
    ApiSocket(
        boost::asio::io_service *io_service,
        boost::asio::ssl::context *ssl_context,
        boost::asio::ssl::verify_mode ssl_verify_mode,
        const char* host,
        unsigned int timeout);
    virtual ~ApiSocket();
    boost::asio::ip::tcp::socket *get_socket();
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
        *get_secure_socket();
    bool is_secure();
    void finish();
    void cancel();
 private:
    void init_timer(boost::asio::io_service *io_service, unsigned int timeout);
 private:
    bool time_expired_;
    boost::asio::deadline_timer *timer_;
    boost::asio::ip::tcp::socket *socket_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> *secure_socket_;
};

}  // namespace apiclient

#endif  // API_CLIENT_API_SOCKET_H_
