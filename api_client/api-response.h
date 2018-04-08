/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_RESPONSE_H_
#define API_CLIENT_API_RESPONSE_H_

#include <string>
#include <sstream>
#include "api_client/apiclient/apiclient.h"

namespace apiclient {

int parse_http_stream(std::stringstream& data, std::string* body,
    ApiHeaders* headers);

}  // namespace apiclient

#endif  // API_CLIENT_API_RESPONSE_H_

