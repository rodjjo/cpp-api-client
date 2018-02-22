/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_TEST_TESTING_H_
#define API_CLIENT_TEST_TESTING_H_

#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif

#ifndef UNIT_TEST
#define UNIT_TEST
#endif

#include <boost/test/unit_test.hpp>

#endif  // API_CLIENT_TEST_TESTING_H_

