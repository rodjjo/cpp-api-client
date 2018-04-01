/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/apiclient/apiclient.h"

namespace apiclient {

Response::Response() {
    error_ = 0;
    status_ = 0;
    has_error_ = false;
    parsed_ = false;
}

Response::Response(int error) {
    error_ = error;
    status_ = 0;
    has_error_ = true;
    parsed_ = false;
}

Response::Response(int status, const std::string& data) {
    error_ = 0;
    status_ = status;
    has_error_ = false;
    parsed_ = false;
}

Response::~Response() {
}

void Response::parse_json() {
    if (parsed_) {
        return;
    }
    parsed_ = true;
}

int Response::get_status() {
    return status_;
}

int Response::get_error() {
    return error_;
}

bool Response::has_error() {
    return has_error_;
}

bool Response::is_json() {
    return false;
}

const Json::Value& Response::get_body() {
    parse_json();
    if (is_json()) {
        return body_;
    }
    return body_;
}

const std::string& Response::get_data() {
    return data_;
}

}  // namespace apiclient
