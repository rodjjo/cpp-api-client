/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/apiclient/apiclient.h"
#include "api_client/asio-client.h"


namespace apiclient {

ApiBase::~ApiBase() {
}

std::shared_ptr<ApiBase> build(const std::string& base_url) {
    return std::shared_ptr<ApiBase> (new ApiClient(base_url));
}


}  // namespace apiclient
