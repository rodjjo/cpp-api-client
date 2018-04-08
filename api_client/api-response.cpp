/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include <string>
#include "api_client/apiclient/apiclient.h"
#include "api_client/api-response.h"

namespace apiclient {

Response::Response() {
    error_ = 0;
    status_ = 0;
    has_error_ = false;
    is_json_ = false;
}

Response::Response(int error) {
    error_ = error;
    status_ = 0;
    has_error_ = true;
    is_json_ = false;
}

Response::Response(const std::string& data,
        const ApiHeaders & headers, int status) {
    error_ = 0;
    status_ = status;
    has_error_ = false;
    data_ = data;
    headers_ = headers;
    is_json_ = Json::Reader().parse(data, body_, false);
}

Response::~Response() {
}

int Response::get_status() const {
    return status_;
}

int Response::get_error() const {
    return error_;
}

bool Response::has_error() const {
    return has_error_;
}

bool Response::is_json() const {
    return is_json_;
}

const Json::Value& Response::get_body() const {
    return body_;
}

const std::string& Response::get_data() const {
    return data_;
}

const ApiHeaders& Response::get_headers() const {
    return headers_;
}

int parse_http_stream(
    std::stringstream& data,
    std::string* body,
    ApiHeaders* headers
) {
    unsigned int status_code = 0;
    data.seekp(0);
    std::string http_version;
    data >> http_version;
    data >> status_code;
    std::string line;
    std::getline(data, line);

    if (!data.good() || http_version.substr(0, 5) != "HTTP/") {
        return 0;
    }

    size_t separator_position;

    while (data.good()) {
        std::getline(data, line);
        if (line.empty() || line == "\r" || line == "\r\n") {
            break;
        }
        separator_position = line.find_first_of(':');
        if (separator_position != std::string::npos) {
            (*headers) [
                line.substr(0, separator_position)
            ] = line.substr(separator_position + 1);
        }
    }

    *body = data.str().substr(data.tellg());

    return status_code;
}

}  // namespace apiclient
