/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/apiclient/apiclient.h"

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

Response::Response(int status, const std::string& data) {
    error_ = 0;
    status_ = status;
    has_error_ = false;
    data_ = data;
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

const std::string& Response::get_data() const{
    return data_;
}

}  // namespace apiclient
