/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/apiclient/apiclient.h"
#include "api_client/client-builder.h"


namespace apiclient {

Client::~Client() {
}

ClientBuilder::~ClientBuilder() {
}

std::shared_ptr<ClientBuilder> builder(unsigned char num_threads) {
    return std::shared_ptr<ClientBuilder> (new ClientBuilderImp(num_threads));
}

}  // namespace apiclient
