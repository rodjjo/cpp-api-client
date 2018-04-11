/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_HTTP_CLIENT_H_
#define API_CLIENT_HTTP_CLIENT_H_

#include <memory>
#include <functional>
#include <string>
#include <boost/thread.hpp>

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#endif

#include "api_client/apiclient/apiclient.h"
#include "api_client/location-resolver.h"
#include "api_client/api-request.h"
#include "api_client/protocol-client.h"
#include "api_client/api-socket.h"


namespace apiclient {

typedef std::shared_ptr<
            boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
        >  sslsocket_t;

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> streamsocket_t;

typedef std::function<void (
        sslsocket_t ssl_socket
)> BuildSocketHandler;


typedef std::function<void (
    const boost::system::error_code& error,
    std::shared_ptr<ApiSocket> socket
)> ConnectHandler;

class HTTPClient: public ProtocolClientBase {
 public:
    HTTPClient(
        std::shared_ptr<ClientIo> client_io, location_t location);
    virtual ~HTTPClient();

    virtual void connect(
        boost::asio::ip::tcp::resolver::iterator iter,
        unsigned int timeout,
        ConnectHandler handler);

    virtual void make_request(
        boost::asio::ip::tcp::resolver::iterator iter,
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout);
 private:
    void process_response(std::shared_ptr<ApiSocket> api_socket,
        std::shared_ptr<boost::asio::streambuf> buffer,
        std::shared_ptr<std::stringstream> data,
        ResponseHandler response_handler);
};

}  // namespace apiclient

#endif  // API_CLIENT_HTTP_CLIENT_H_
