/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/client-builder.h"
#include "api_client/asio-client.h"

namespace apiclient {


ClientBuilder::~ClientBuilder() {
}

std::shared_ptr<ClientBase> ClientBuilder::client(
        const std::string& base_url) {
    return std::shared_ptr<ClientBase>(new Client(base_url));
}

}  // namespace apiclient
