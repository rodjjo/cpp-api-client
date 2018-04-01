/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/http-client.h"


namespace apiclient {

HTTPClient::HTTPClient(std::shared_ptr<ClientIo> client_io,
    url_fragments_t url_fragments) :
        ProtocolClientBase(client_io, url_fragments.host, url_fragments.port) {
}

HTTPClient::~HTTPClient() {
}

void HTTPClient::make_request(
    std::shared_ptr<boost::asio::streambuf> message,
    ResponseHandler response_handler,
    int timeout
) {

}

}  // namespace apiclient
