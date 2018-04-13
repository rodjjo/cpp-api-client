/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_ASIO_H_
#define API_CLIENT_API_ASIO_H_

#ifdef UNIT_TEST
#include "api_client/test/mocks/asio.hpp"
#else
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#define ERROR_VALUE_SSL_SHORT_READ ERR_PACK(ERR_LIB_SSL, 0, SSL_R_SHORT_READ)
#endif

namespace apiclient {

namespace asio_ssl = boost::asio::ssl;

}  // namespace apiclient

#endif  // API_CLIENT_API_ASIO_H_
