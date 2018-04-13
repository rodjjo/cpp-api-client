/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_CLIENT_IO_H_
#define API_CLIENT_API_CLIENT_IO_H_


#include <memory>
#include <list>
#include <functional>
#include <string>
#include <boost/thread.hpp>

#include "api_client/api-asio.h"

namespace apiclient {

class ClientIo {
 public:
    explicit ClientIo(unsigned char num_threads);
    virtual ~ClientIo();

    boost::asio::io_service io_service;

 private:
    std::shared_ptr<boost::asio::io_service::work> work_;
    std::list<std::shared_ptr<boost::thread> > threads_;
};

}  // namespace apiclient


#endif  // API_CLIENT_API_CLIENT_IO_H_
