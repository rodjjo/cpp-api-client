/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/test/testing.h"
#include "api_client/api-exception.h"
#include "api_client/asio-resolver.h"

class Fixture {
 public:
  Fixture() {
    boost::reset_mocks();
  }
};


BOOST_FIXTURE_TEST_SUITE(resolver_test_suite, Fixture)


BOOST_AUTO_TEST_CASE(test_asio_resolver_except) {
  boost::asio::io_service io_service;
  apiclient::Resolver resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = boost::system::errc::make_error_code(
                boost::system::errc::bad_address);

  BOOST_CHECK_THROW(resolver.resolve(), apiclient::ApiException);
}

BOOST_AUTO_TEST_CASE(test_asio_resolver_sync_resolve) {
  boost::asio::io_service io_service;
  apiclient::Resolver resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = boost::system::errc::make_error_code(
                boost::system::errc::success);
  resolver.resolve();
  BOOST_CHECK(boost::asio::ip::tcp::resolver::resolve_called_);
  boost::asio::ip::tcp::resolver::resolve_called_ = false;
  resolver.resolve();
  BOOST_CHECK(!boost::asio::ip::tcp::resolver::resolve_called_);
}

BOOST_AUTO_TEST_CASE(test_asio_resolver_assync_resolve_error) {
  boost::asio::io_service io_service;
  apiclient::Resolver resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = boost::system::errc::make_error_code(
      boost::system::errc::bad_address);

  bool handler_called = false;
  auto handler = [&handler_called](const boost::system::error_code& e,
                    boost::asio::ip::tcp::resolver::iterator) {
    handler_called = true;
    BOOST_CHECK(e);
  };
  resolver.resolve(handler);
  BOOST_CHECK(handler_called);
  BOOST_CHECK(boost::asio::ip::tcp::resolver::async_resolve_called_);
}

BOOST_AUTO_TEST_CASE(test_asio_resolver_assync_resolve) {
  boost::asio::io_service io_service;
  apiclient::Resolver resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = boost::system::errc::make_error_code(
    boost::system::errc::success);

  bool handler_called = false;
  auto handler = [&handler_called](const boost::system::error_code& e,
                    boost::asio::ip::tcp::resolver::iterator) {
    handler_called = true;
    BOOST_CHECK(!e);
  };

  resolver.resolve(handler);

  BOOST_CHECK(handler_called);
  BOOST_CHECK(boost::asio::ip::tcp::resolver::async_resolve_called_);

  boost::asio::ip::tcp::resolver::async_resolve_called_ = false;
  resolver.resolve(handler);
  BOOST_CHECK(boost::asio::ip::tcp::resolver::async_resolve_called_);
}

BOOST_AUTO_TEST_SUITE_END()
