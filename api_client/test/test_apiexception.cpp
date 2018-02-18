/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#define BOOST_TEST_MAIN

#include "testing.h"
#include "../api-exception.h"

BOOST_AUTO_TEST_CASE(test_api_exception) {
    auto error = apiclient::ApiException("Test Message");

    BOOST_CHECK_EQUAL("Test Message", error.what());
}
