/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_CLIENT_BUILDER_H_
#define API_CLIENT_CLIENT_BUILDER_H_

#include <string>
#include "api_client/apiclient/apiclient.h"
#include "api_client/asio-client.h"


namespace apiclient {

class ClientBuilder: public ClientBuilderBase {
 public:
  ClientBuilder();
  virtual ~ClientBuilder();
  std::shared_ptr<ClientBase> client(const std::string& base_url) override;
 private:
  std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient


#endif  // API_CLIENT_CLIENT_BUILDER_H_
