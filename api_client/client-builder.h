/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_CLIENT_BUILDER_H_
#define API_CLIENT_CLIENT_BUILDER_H_

#include <string>
#include "api_client/apiclient/apiclient.h"
#include "api_client/api-client-io.h"


namespace apiclient {

class ClientBuilderImp: public ClientBuilder {
 public:
  explicit ClientBuilderImp(unsigned char num_threads);
  virtual ~ClientBuilderImp();
  std::shared_ptr<Client> client(const std::string& base_url) override;
 private:
  std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient


#endif  // API_CLIENT_CLIENT_BUILDER_H_
