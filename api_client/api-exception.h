/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_API_EXCEPTION_H_
#define API_CLIENT_API_EXCEPTION_H_

#include <exception>
#include <string>

namespace apiclient {

class ApiException: public std::exception {
 public:
  explicit ApiException(const std::string& message);
  virtual ~ApiException() throw();
  virtual const char* what() const throw();

 private:
  std::string message_;
};

}  // namespace apiclient

#endif  // API_CLIENT_API_EXCEPTION_H_
