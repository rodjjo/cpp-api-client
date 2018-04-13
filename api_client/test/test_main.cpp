/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#define BOOST_TEST_MAIN

#include "api_client/test/testing.h"
#include "api_client/apiclient/apiclient.h"

BOOST_AUTO_TEST_CASE(test_apiclient_build) {
  auto pool = apiclient::pool(1);
  auto client = pool->api("http://www.example.com/api/");

  BOOST_CHECK(client.get() != NULL);
}

BOOST_AUTO_TEST_CASE(test_apiclient_build_error) {
  auto pool = apiclient::pool(1);
  BOOST_CHECK_THROW(pool->api("this is not a valid url"),
    std::exception);
}
