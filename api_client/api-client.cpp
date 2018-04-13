/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/apiclient/apiclient.h"
#include "api_client/api-pool-imp.h"


namespace apiclient {

Client::~Client() {
}

ApiPool::~ApiPool() {
}

std::shared_ptr<ApiPool> pool(unsigned char num_threads) {
    return std::shared_ptr<ApiPool> (new ApiPoolImp(num_threads));
}

}  // namespace apiclient
