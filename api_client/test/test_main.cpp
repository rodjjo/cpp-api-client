/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#define BOOST_TEST_MAIN

#include "api_client/test/testing.h"
#include "api_client/apiclient/apiclient.h"

BOOST_AUTO_TEST_CASE(test_apiclient_build) {
    auto client = apiclient::build("http://www.example.com/api/");

    BOOST_CHECK(client.get() != NULL);
}

BOOST_AUTO_TEST_CASE(test_apiclient_build_error) {
  try {
    auto client = apiclient::build("not a valid url");
    BOOST_ASSERT_MSG(false, "Api Exception Expected");
  } catch(const std::exception &e) {
    BOOST_CHECK_EQUAL("Invalid url: not a valid url", e.what());
  }
}
