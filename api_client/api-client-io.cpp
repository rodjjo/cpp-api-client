/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/api-client-io.h"

namespace apiclient {

ClientIo::ClientIo(unsigned char num_threads) {
    if (num_threads < 1) {
        num_threads = 1;
    }
    work_.reset(new boost::asio::io_service::work(io_service));
    for (unsigned char c = 0; c < num_threads; ++c) {
        threads_.push_back(
            std::shared_ptr<boost::thread> (
                new boost::thread([this] () {
                    io_service.reset();
                    io_service.run();
                })));
    }
}

ClientIo::~ClientIo() {
    work_.reset();
    io_service.stop();
    for (auto it = threads_.begin(); it != threads_.end(); ++it) {
        (*it)->join();
    }
}

}  // namespace apiclient
