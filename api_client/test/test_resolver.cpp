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
  auto resolver = apiclient::get_resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = 10;
  try {
    resolver->resolve();
    BOOST_ASSERT_MSG(false, "Api Exception Expected");
  } catch(const apiclient::ApiException &e) {
    BOOST_CHECK_EQUAL("Fail resolving host: google.com", e.what());
  }
}

BOOST_AUTO_TEST_CASE(test_asio_resolver_sync_resolve) {
  boost::asio::io_service io_service;
  auto resolver = apiclient::get_resolver(&io_service, "google.com", 8080);
  boost::asio::ip::tcp::resolver::error_ = 0;
  resolver->resolve();
  BOOST_CHECK_EQUAL(true, boost::asio::ip::tcp::resolver::resolve_called_);
  boost::asio::ip::tcp::resolver::resolve_called_ = false;
  resolver->resolve();
  BOOST_CHECK_EQUAL(false, boost::asio::ip::tcp::resolver::resolve_called_);
}

BOOST_AUTO_TEST_SUITE_END()
