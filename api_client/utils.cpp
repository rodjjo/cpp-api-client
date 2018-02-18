/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include <regex>  // NOLINT google likes re2
#include <cstdlib>
#include "./utils.h"


namespace apiclient {
namespace {
  std::regex url_regex1(
    "^(http|https)://([_a-z0-9\\-\\.]+)(\\:[0-9]+|\\:[0-9]+\\/|\\/).*");
  std::regex url_regex2(
    "^(http|https)://([_a-z0-9\\-\\.]+).*");
  std::regex content_regex("^Content-Type", std::regex_constants::icase);
  std::regex json_regex("^application\\/json", std::regex_constants::icase);
}  // unnamed namespace

bool is_json_content_type(const std::pair<std::string, std::string> &header) {
  return std::regex_search(header.first, content_regex) &&
    std::regex_search(header.second, json_regex);
}

url_fragments_t decompose_url(const std::string& url) {
  std::cmatch base_match;
  auto matched = std::regex_match(url.c_str(), base_match, url_regex1);

  url_fragments_t result;
  result.port = 80;
  result.valid = false;
  result.secure = false;

  if (!matched) {
    matched = std::regex_match(url.c_str(), base_match, url_regex2);
    if (!matched) return result;
  }

  if (base_match.size() >= 3) {
    result.valid = 3;
    if (base_match[1].str() == "https") {
      result.secure = true;
      result.port = 443;
    }
    result.host = base_match[2].str();
    if (base_match.size() == 4 && base_match[3].str() != "/") {
      result.port = atoi(base_match[3].str().c_str() + 1);
    }
  }

  return result;
}

}  // namespace apiclient

