/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/api-client-imp.h"
#include "api_client/client-builder.h"

namespace apiclient {

ClientBuilderImp::ClientBuilderImp(unsigned char num_threads):
    client_io_(new ClientIo(num_threads)
) {
}

ClientBuilderImp::~ClientBuilderImp() {
}

std::shared_ptr<Client> ClientBuilderImp::client(
        const std::string& base_url) {
    return std::shared_ptr<Client>(new ClientImp(client_io_, base_url));
}

}  // namespace apiclient
