/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include <atomic>
#include "api_client/asio-resolver.h"
#include "api_client/api-exception.h"


namespace apiclient {

ResolverBase::~ResolverBase() {
}

class Resolver: public ResolverBase {
 public:
  Resolver(boost::asio::io_service *io_service, const std::string& host,
           int port);
    virtual boost::asio::ip::tcp::resolver::iterator resolve();
    virtual void resolve(ResolverHandler handler);
    virtual bool resolved();
 private:
    int port_;
    std::string host_;
    std::atomic_bool updating_;
    std::atomic_bool updated_;
    boost::asio::io_service *io_service_;
    std::shared_ptr<boost::asio::ip::tcp::resolver::iterator> iterator_;
};

Resolver::Resolver(boost::asio::io_service *io_service,
    const std::string& host, int port) {
  host_ = host;
  port_ = port;
  updating_ = false;
  updated_ = false;
  io_service_ = io_service;
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

std::shared_ptr<ResolverBase> get_resolver(boost::asio::io_service *io_service,
    const std::string& host, int port) {
  return std::shared_ptr<ResolverBase>(new Resolver(io_service, host, port));
}


}  // namespace apiclient
