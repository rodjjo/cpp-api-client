/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/location-resolver.h"
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
      if (!error && updating_.exchange(true) == false) {
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

boost::asio::ip::tcp::resolver::iterator *Resolver::get() {
  if (resolved()) {
    return iterator_.get();
  }
  return NULL;
}

}  // namespace apiclient
