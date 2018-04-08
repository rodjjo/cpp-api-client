/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/test/mocks/asio.hpp"


std::string boost::asio::ip::tcp::resolver::query::host_; // NOLINT
std::string boost::asio::ip::tcp::resolver::query::service_; // NOLINT
boost::asio::ip::tcp::resolver::iterator boost::asio::ip::tcp::resolver::iterator_; // NOLINT
boost::system::error_code boost::asio::ip::tcp::resolver::error_; // NOLINT
bool boost::asio::ip::tcp::resolver::resolve_called_ = false;
bool boost::asio::ip::tcp::resolver::async_resolve_called_ = false;

void boost::reset_mocks() {
    boost::asio::ip::tcp::resolver::query::host_ = std::string();
    boost::asio::ip::tcp::resolver::query::service_ = std::string();
    boost::asio::ip::tcp::resolver::error_ =
        boost::system::errc::make_error_code(boost::system::errc::success);
    boost::asio::ip::tcp::resolver::resolve_called_ = false;
    boost::asio::ip::tcp::resolver::async_resolve_called_ = false;
}


void SSL_set_tlsext_host_name(SSL* handle, const char *hosts) {
}

namespace boost {
namespace asio {

void async_connect(
    boost::asio::ip::tcp::socket& s,
    boost::asio::ip::tcp::resolver::iterator begin,
    ComposedConnectHandler handler) {

}

void async_write(boost::asio::ip::tcp::socket& s,
    boost::asio::streambuf &buffer,
    WriteHandler handler) {

}

void async_read(boost::asio::ip::tcp::socket& s,
                boost::asio::streambuf &buffer,
                int transferr,
                ReadHandler read_handler
            ) {

}

int transfer_at_least(int value) {
  return value;
}



namespace error {

namespace detail {

class ssl_category : public boost::system::error_category
{
public:
  const char* name() const BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT
  {
    return "asio.ssl";
  }

  std::string message(int value) const
  {
    return "asio.ssl error";
  }
};

}  // namespace detail

const boost::system::error_category & get_ssl_category() {
  static detail::ssl_category instance;
  return instance;
}

}  // namespace error
}  // namespace asio
}  // namespace boost
