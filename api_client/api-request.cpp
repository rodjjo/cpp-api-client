/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include <ostream>
#include "api_client/api-request.h"

namespace apiclient {

const char *METHODS[] = {
    "GET",
    "POST",
    "PUT",
    "PATCH",
    "DELETE"
};

void compose_request(http_method_t method,
                    const std::string& host,
                    const std::string &query,
                    const ApiHeaders &headers,
                    const std::string& body,
                    boost::asio::streambuf *message) {
    std::ostream output(message);
    output << METHODS[method] << " " << query << " HTTP/1.0\r\n";
    output << "Host: " << host << "\r\n";
    output << "Accept: */*\r\n";

    for (auto it = headers.begin(); it != headers.end(); ++it) {
        output << it->first << ": " << it->second << "\r\n";
    }

    if (method != http_get && body.size() > 0) {
        output << "Content-Type: application/json\r\n";
        output << "Content-Length: " << body.size() << "\r\n";
    } else {
        output << "Content-Length: 0\r\n";
    }

    output << "Connection: close\r\n\r\n";

    if (method != http_get) {
        output << body;
    }
}

void compose_request(http_method_t method,
                    const std::string& host,
                    const std::string &query,
                    const ApiHeaders &headers,
                    boost::asio::streambuf *message) {
    compose_request(method, host, query, headers, std::string(), message);
}

void compose_request(http_method_t method,
                    const std::string& host,
                    const std::string &query,
                    const ApiHeaders &headers,
                    const Json::Value &body,
                    boost::asio::streambuf *message) {
    Json::FastWriter writer;
    compose_request(method, host, query, headers, writer.write(body), message);
}

}  // namespace apiclient
