/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_CLIENT_BUILDER_H_
#define API_CLIENT_CLIENT_BUILDER_H_

#include <string>
#include "api_client/apiclient/apiclient.h"


namespace apiclient {

class ClientBuilder: public ClientBuilderBase {
 public:
  virtual ~ClientBuilder();
  std::shared_ptr<ClientBase> client(const std::string& base_url) override;
};

} // namespace apiclient


#endif  // API_CLIENT_CLIENT_BUILDER_H_
