/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/client-builder.h"

namespace apiclient {

ClientBuilder::ClientBuilder(): client_io_(new ClientIo()) {
}

ClientBuilder::~ClientBuilder() {
}

std::shared_ptr<ClientBase> ClientBuilder::client(
        const std::string& base_url) {
    return std::shared_ptr<ClientBase>(new Client(client_io_, base_url));
}

}  // namespace apiclient
