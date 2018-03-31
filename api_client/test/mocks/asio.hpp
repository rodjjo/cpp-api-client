/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_TEST_MOCKS_ASIO_HPP_
#define API_CLIENT_TEST_MOCKS_ASIO_HPP_

#include <string>
#include <sstream>
#include <functional>
#include <boost/system/error_code.hpp>
#include <boost/asio/streambuf.hpp>


typedef int SSL;

namespace boost {
namespace asio {

namespace ssl {

enum {
  verify_none = 0,
};

typedef int verify_mode;

class verify_context {
  public:
};

class context {
 public:
  typedef enum {
    tlsv12 = 1
  } version_t;

  explicit context(version_t ver) {
  }


  void set_default_verify_paths() {
  }
};

}

class io_service {
 public:
  class work {
   public:
    explicit work(const io_service &service) {
    }
  };

  void reset() {
  }

  void run() {
  }

  void stop() {
  }
};

namespace ip {
namespace tcp {

class resolver {
 public:
  explicit resolver(const boost::asio::io_service& io_service):
    io_service_(io_service) {
  }

  const boost::asio::io_service& io_service_;

  class query {
   public:
     query(const std::string& host, const std::string& service) {
        host_ = host;
        service_ = service;
     }
     static std::string host_;
     static std::string service_;
  };

  class iterator {
   public:
  };

  static iterator iterator_;
  static boost::system::error_code error_;
  static bool resolve_called_;
  static bool async_resolve_called_;

  void async_resolve(const query& query,
    std::function<void(const boost::system::error_code error,
        iterator)> handler) {
    async_resolve_called_ = true;
    handler(error_, iterator_);
  }

  iterator resolve(const query& query, boost::system::error_code &error) {  // NOLINT
    resolve_called_ = true;
    error = error_;
    return iterator_;
  }
};

class socket {
 public:
  socket(boost::asio::io_service& io_service, boost::asio::ssl::context& context) {
  }

  socket& lowest_layer() {
    return *this;
  }


  void set_verify_mode(boost::asio::ssl::verify_mode mode) {
  }

  void set_verify_callback(std::function<bool(bool, boost::asio::ssl::verify_context&)> clb) {
  }

  SSL* native_handle() {
    return (SSL*) 0;
  }
};

}  // namespace tcp
}  // namespace ip


typedef std::function<void(
    const boost::system::error_code&,
    boost::asio::ip::tcp::resolver::iterator
  )> ComposedConnectHandler;

void async_connect(boost::asio::ip::tcp::socket& s,
    boost::asio::ip::tcp::resolver::iterator begin,
    ComposedConnectHandler handler);


namespace ssl {

template<typename sock_type>
class stream: public boost::asio::ip::tcp::socket {
  public:
    stream(boost::asio::io_service& io_service, boost::asio::ssl::context& context): socket(io_service, context) {
    }

};

}
}  // namespace asio

void reset_mocks();

}  // namespace boost

void SSL_set_tlsext_host_name(SSL* handle, const char *hosts);

#endif  // API_CLIENT_TEST_MOCKS_ASIO_HPP_

