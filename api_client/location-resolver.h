/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_LOCATION_RESOLVER_H_
#define API_CLIENT_LOCATION_RESOLVER_H_

#include <atomic>
#include <memory>
#include <string>
#include <functional>

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#endif

namespace apiclient {

typedef std::function<void(const boost::system::error_code&,
    boost::asio::ip::tcp::resolver::iterator)> ResolverHandler;

class Resolver {
 public:
    Resolver(boost::asio::io_service *io_service, const std::string& host,
           int port);
    virtual ~Resolver();
    void resolve(ResolverHandler handler);
    bool resolved();
    boost::asio::ip::tcp::resolver::iterator *get();
 private:
    int port_;
    std::string host_;
    std::atomic_bool updating_;
    std::atomic_bool updated_;
    boost::asio::io_service *io_service_;
    std::shared_ptr<boost::asio::ip::tcp::resolver::iterator> iterator_;
};

}  // namespace apiclient

#endif  // API_CLIENT_LOCATION_RESOLVER_H_
