/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/apiclient/apiclient.h"
#include "api_client/client-builder.h"


namespace apiclient {

ClientBase::~ClientBase() {
}

ClientBuilderBase::~ClientBuilderBase() {
}

std::shared_ptr<ClientBuilderBase> builder(unsigned char num_threads) {
    return std::shared_ptr<ClientBuilderBase> (new ClientBuilder(num_threads));
}

}  // namespace apiclient
