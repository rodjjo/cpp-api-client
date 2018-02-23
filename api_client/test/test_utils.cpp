/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
/*
#include "api_client/test/testing.h"
#include "api_client/utils.h"

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

BOOST_AUTO_TEST_CASE(test_decompose_url_invalid) {
    std::string url1("ftp://testeurl/");
    std::string url2("http://");
    std::string url3("http://:9090");
    std::string url4("http:///");
    std::string url5("https://:9111");
    BOOST_CHECK_EQUAL(false, apiclient::decompose_url(url1).valid);
    BOOST_CHECK_EQUAL(false, apiclient::decompose_url(url2).valid);
    BOOST_CHECK_EQUAL(false, apiclient::decompose_url(url3).valid);
    BOOST_CHECK_EQUAL(false, apiclient::decompose_url(url4).valid);
    BOOST_CHECK_EQUAL(false, apiclient::decompose_url(url5).valid);
}

BOOST_AUTO_TEST_CASE(test_decompose_url_valid) {
    std::string url1("http://testeurl1/");
    std::string url2("https://testeurl2/");
    std::string url3("https://testeurl3:9090/");
    std::string url4("http://testeurl4:8080/");
    std::string url5("http://testeurl5:8080");
    std::string url6("https://testeurl6:9090");

    apiclient::url_fragments_t url_frag1 = apiclient::decompose_url(url1);
    apiclient::url_fragments_t url_frag2 = apiclient::decompose_url(url2);
    apiclient::url_fragments_t url_frag3 = apiclient::decompose_url(url3);
    apiclient::url_fragments_t url_frag4 = apiclient::decompose_url(url4);
    apiclient::url_fragments_t url_frag5 = apiclient::decompose_url(url5);
    apiclient::url_fragments_t url_frag6 = apiclient::decompose_url(url6);

    BOOST_CHECK_EQUAL(true, url_frag1.valid);
    BOOST_CHECK_EQUAL(true, url_frag2.valid);
    BOOST_CHECK_EQUAL(true, url_frag3.valid);
    BOOST_CHECK_EQUAL(true, url_frag4.valid);
    BOOST_CHECK_EQUAL(true, url_frag5.valid);
    BOOST_CHECK_EQUAL(true, url_frag6.valid);

    BOOST_CHECK_EQUAL("testeurl1", url_frag1.host);
    BOOST_CHECK_EQUAL("testeurl2", url_frag2.host);
    BOOST_CHECK_EQUAL("testeurl3", url_frag3.host);
    BOOST_CHECK_EQUAL("testeurl4", url_frag4.host);
    BOOST_CHECK_EQUAL("testeurl5", url_frag5.host);
    BOOST_CHECK_EQUAL("testeurl6", url_frag6.host);

    BOOST_CHECK_EQUAL(80, url_frag1.port);
    BOOST_CHECK_EQUAL(443, url_frag2.port);
    BOOST_CHECK_EQUAL(9090, url_frag3.port);
    BOOST_CHECK_EQUAL(8080, url_frag4.port);
    BOOST_CHECK_EQUAL(8080, url_frag5.port);
    BOOST_CHECK_EQUAL(9090, url_frag6.port);
}
*/
