/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_POOL_IMP_H_
#define API_CLIENT_API_POOL_IMP_H_

#include <string>
#include "api_client/apiclient/apiclient.h"
#include "api_client/api-client-io.h"


namespace apiclient {

class ApiPoolImp: public ApiPool {
 public:
  explicit ApiPoolImp(unsigned char num_threads);
  virtual ~ApiPoolImp();
  std::shared_ptr<Client> api(const std::string& base_url) override;
 private:
  std::shared_ptr<ClientIo> client_io_;
};

}  // namespace apiclient


#endif  // API_CLIENT_API_POOL_IMP_H_
