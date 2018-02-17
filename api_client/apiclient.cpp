/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "apiclient/apiclient.h"

namespace apiclient {

ApiBase::~ApiBase() {
}

std::shared_ptr<ApiBase> build(const std::string& base_url) {
    return std::shared_ptr<ApiBase> ();
}

}  // namespace apiclient
