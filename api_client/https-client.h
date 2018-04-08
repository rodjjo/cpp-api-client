/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_HTTPS_CLIENT_H_
#define API_CLIENT_HTTPS_CLIENT_H_

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
#include "api_client/protocol-client.h"

namespace apiclient {

typedef std::shared_ptr<
            boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
        >  sslsocket_t;

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> streamsocket_t;

typedef std::function<void (
        sslsocket_t ssl_socket
    )> BuildSocketHandler;

class HTTPSClient: public ProtocolClientBase {
 public:
    HTTPSClient(std::shared_ptr<ClientIo> client_io,
        location_t location,
        asio_ssl::verify_mode ssl_verify_mode);
    virtual ~HTTPSClient();

    void make_request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout) override;

 protected:

    bool verify_certificate(bool preverified, asio_ssl::verify_context& ctx);

    void build_ssl_socket(BuildSocketHandler handler);

    void process_request(
        sslsocket_t ssl_socket,
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler);
    void process_response(
        sslsocket_t ssl_socket,
        ResponseHandler response_handler
    );

    void request(std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout = 0);
 private:
    asio_ssl::verify_mode ssl_verify_mode_;
    std::shared_ptr<boost::asio::ssl::context> ssl_context_;
};

}  // namespace apiclient

#endif  // API_CLIENT_HTTPS_CLIENT_H_
