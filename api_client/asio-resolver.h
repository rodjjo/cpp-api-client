/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_ASIO_RESOLVER_H_
#define API_CLIENT_ASIO_RESOLVER_H_

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

class ResolverBase {
 public:
    virtual ~ResolverBase();
    virtual bool resolved() = 0;
    virtual boost::asio::ip::tcp::resolver::iterator resolve() = 0;
    virtual void resolve(ResolverHandler handler) = 0;
};


std::shared_ptr<ResolverBase> get_resolver(boost::asio::io_service *io_service,
  const std::string& host, int port);


}  // namespace apiclient

#endif  // API_CLIENT_ASIO_RESOLVER_H_
