/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_TEST_MOCKS_ASIO_HPP_
#define API_CLIENT_TEST_MOCKS_ASIO_HPP_

#include <string>
#include <functional>

namespace boost {

namespace system {

class error_code {
 public:
    error_code() {
      error_ = 0;
    }

    explicit error_code(int value) {
      error_ = value;
    }


    error_code& operator=(int value) noexcept {
      error_ = value;
      return *this;
    }

    operator bool() {
      return error_ != 0;
    }

    operator int() {
      return error_;
    }

 private:
    int error_;
};

}  // namespace system

namespace asio {

class io_service {
 public:
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

  void async_resolve(const query& query,
    std::function<void(const boost::system::error_code error,
        iterator)> handler) {
    handler(error_, iterator_);
  }

  iterator resolve(const query& query, boost::system::error_code &error) {  // NOLINT
    resolve_called_ = true;
    error = error_;
    return iterator_;
  }
};

}  // namespace tcp
}  // namespace ip
}  // namespace asio

void reset_mocks();

}  // namespace boost

#endif  // API_CLIENT_TEST_MOCKS_ASIO_HPP_

