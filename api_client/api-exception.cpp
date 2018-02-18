/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api-exception.h"

namespace apiclient {

ApiException::ApiException(const std::string& message): message_(message) {
}

ApiException::~ApiException() throw() {
}

const char* ApiException::what() const throw() {
  return message_.c_str();
}

}  // namespace apiclient
