/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_CLIENT_IMP_H_
#define API_CLIENT_API_CLIENT_IMP_H_


#include <memory>
#include <list>
#include <functional>
#include <string>
#include <boost/thread.hpp>

#include "api_client/api-asio.h"
#include "api_client/apiclient/apiclient.h"
#include "api_client/protocol-client.h"


namespace apiclient {

class ClientImp: public Client {
 public:
    ClientImp(std::shared_ptr<ClientIo> client_io,
        const std::string& base_url,
        asio_ssl::verify_mode ssl_verify_mode = asio_ssl::verify_none);
    virtual ~ClientImp();
    void get(const std::string& query_string,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void post(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void put(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void del(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;
    void patch(const std::string& query_string,
        const Json::Value& body,
        ResponseHandler response_handler,
        int timeout = 0, const ApiHeaders *headers = NULL) override;

 private:
    const std::string& get_host();
    std::shared_ptr<boost::asio::streambuf> get_message(
        http_method_t method,
        const std::string& query_string,
        const Json::Value* body,
        const ApiHeaders *headers = NULL);

    std::shared_ptr<ProtocolClient> client_;
};


}  // namespace apiclient

#endif  // API_CLIENT_API_CLIENT_IMP_H_
