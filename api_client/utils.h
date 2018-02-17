/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#ifndef API_CLIENT_UTILS_H_
#define API_CLIENT_UTILS_H_

#include <utility>
#include <string>

namespace apiclient {

typedef struct {
  bool valid;
  bool secure;
  std::string host;
  int port;
} url_fragments_t;

bool is_json_content_type(const std::pair<std::string, std::string> &header);
url_fragments_t decompose_url(const std::string& url);

}  // namespace apiclient

#endif  // API_CLIENT_UTILS_H_
