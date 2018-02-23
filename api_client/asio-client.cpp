/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/utils.h"
#include "api_client/api-exception.h"
#include "api_client/asio-client.h"


namespace apiclient {


ClientIo::ClientIo() {
    work_.reset(new boost::asio::io_service::work(io_service));
    thread_.reset(new std::thread([this] () {
        io_service.reset();
        io_service.run();
    }));
}

ClientIo::~ClientIo() {
    work_.reset();
    io_service.stop();
    thread_->join();
}


Client::Client(std::shared_ptr<ClientIo> client_io,
        const std::string& base_url) : base_url_(base_url) {
  url_fragments_t fragments = apiclient::decompose_url(base_url);
  if (!fragments.valid) {
    throw ApiException((std::string("Invalid url: ") + base_url).c_str());
  }
  secure_ = fragments.secure;
  host_ = fragments.host;
  port_ = fragments.port;
  client_io_ = client_io;
  resolver_.reset(new Resolver(&client_io_->io_service, host_, port_));
}

Client::~Client() {
}

Response Client::get(const std::string& query_string,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::post(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::put(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::del(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

Response Client::patch(const std::string& query_string,
        const Json::Value& body,
        int timeout, const ApiHeaders *headers) {
    return Response();
}

void Client::patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout, const ApiHeaders *headers) {
}

}  // namespace apiclient
