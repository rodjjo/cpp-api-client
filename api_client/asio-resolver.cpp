/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/asio-resolver.h"
#include "api_client/api-exception.h"


namespace apiclient {

Resolver::Resolver(boost::asio::io_service *io_service,
    const std::string& host, int port) {
  host_ = host;
  port_ = port;
  updating_ = false;
  updated_ = false;
  io_service_ = io_service;
}

Resolver::~Resolver() {
}

void Resolver::resolve(ResolverHandler handler) {
  char port[20] = "";
  snprintf(port, sizeof(port) - 1, "%d", port_);
  boost::asio::ip::tcp::resolver resolver(*io_service_);
  boost::asio::ip::tcp::resolver::query query(host_, port);

  resolver.async_resolve(
    query, [this, handler] (
        const boost::system::error_code& error,
        boost::asio::ip::tcp::resolver::iterator iterator) {
      if (updating_.exchange(true) == false) {
        iterator_.reset(
          new boost::asio::ip::tcp::resolver::iterator(iterator));
        updated_ = true;
      }
      handler(error, iterator);
    });
}

bool Resolver::resolved() {
  return updated_.load();
}

boost::asio::ip::tcp::resolver::iterator Resolver::resolve() {
  if (resolved()) {
    return *iterator_.get();
  }

  char port[20] = "";
  snprintf(port, sizeof(port) - 1, "%d", port_);

  boost::asio::ip::tcp::resolver resolver(*io_service_);
  boost::asio::ip::tcp::resolver::query query(host_, port);
  boost::system::error_code error;

  std::shared_ptr<boost::asio::ip::tcp::resolver::iterator> iter(
    new boost::asio::ip::tcp::resolver::iterator(
      resolver.resolve(query, error)));

  if (error) {
    throw ApiException(std::string("Fail resolving host: ") + host_);
  }

  if (updating_.exchange(true) == false) {
    iterator_ = iter;
    updated_ = true;
  }

  return *iter.get();
}

}  // namespace apiclient
