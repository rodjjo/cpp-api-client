/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_PROTOCOL_CLIENT_H_
#define API_CLIENT_PROTOCOL_CLIENT_H_

#include <memory>
#include <list>
#include <functional>
#include <string>
#include <boost/thread.hpp>

#include "api_client/api-asio.h"
#include "api_client/location-resolver.h"
#include "api_client/api-request.h"
#include "api_client/api-client-io.h"

namespace apiclient {

class ProtocolClient {
 public:
    ProtocolClient(
        std::shared_ptr<ClientIo> client_io,
        const std::string& host,
        int port);

    virtual ~ProtocolClient();
    virtual void make_request(
        boost::asio::ip::tcp::resolver::iterator iter,
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout) = 0;
    void resolve(ResolverHandler handler);
    const std::string& get_host();
    boost::asio::ip::tcp::resolver::iterator& get_resolver_iterator();
    boost::asio::io_service* get_io_service();
    void delivery_response(
        std::stringstream& data,
        ResponseHandler response_handler);
    void make_request(
        std::shared_ptr<boost::asio::streambuf> message,
        ResponseHandler response_handler,
        int timeout);

 private:
    std::shared_ptr<Resolver> resolver_;
    std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient

#endif  // API_CLIENT_PROTOCOL_CLIENT_H_
