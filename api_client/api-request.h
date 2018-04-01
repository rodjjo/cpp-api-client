/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_REQUEST_H_
#define API_CLIENT_API_REQUEST_H_

#include <jsoncpp/json/json.h>
#include <string>
#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#endif
#include "api_client/apiclient/apiclient.h"

namespace apiclient {

typedef enum {
    http_get = 0,
    http_post = 1,
    http_put = 2,
    http_patch = 3,
    http_delete = 4
} http_method_t;

void compose_request(http_method_t method,
                    const std::string& host,
                    const std::string &query,
                    const ApiHeaders *headers,
                    const Json::Value *body,
                    boost::asio::streambuf *message);


}  // namespace apiclient

#endif  // API_CLIENT_API_REQUEST_H_
