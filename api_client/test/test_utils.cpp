/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "testing.h"
#include "../utils.h"

BOOST_AUTO_TEST_CASE(test_is_json_content_type_no_json) {
    std::pair<std::string, std::string> c1("other_header", "other_content");
    std::pair<std::string, std::string> c2("Content-Type", "other_content");
    std::pair<std::string, std::string> c3("other_header", "Application/Json");
    BOOST_CHECK_EQUAL(false, apiclient::is_json_content_type(c1));
    BOOST_CHECK_EQUAL(false, apiclient::is_json_content_type(c2));
    BOOST_CHECK_EQUAL(false, apiclient::is_json_content_type(c3));
}

BOOST_AUTO_TEST_CASE(test_is_json_content_type_with_json) {
    std::pair<std::string, std::string> c1("Content-Type", "Application/Json");
    std::pair<std::string, std::string> c2("content-Type", "application/json");
    BOOST_CHECK_EQUAL(true, apiclient::is_json_content_type(c1));
    BOOST_CHECK_EQUAL(true, apiclient::is_json_content_type(c2));
}
