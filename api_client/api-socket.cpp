/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */

#include "api_client/api-socket.h"

namespace apiclient {

ApiSocket::ApiSocket(
    boost::asio::io_service *io_service, unsigned int timeout
) {
    secure_socket_ = NULL;
    timer_ = NULL;
    time_expired_ = false;
    socket_ = new boost::asio::ip::tcp::socket(*io_service);
    init_timer(io_service, timeout);
}

ApiSocket::ApiSocket(
        boost::asio::io_service *io_service,
        boost::asio::ssl::context *ssl_context,
        boost::asio::ssl::verify_mode ssl_verify_mode,
        const char *host,
        unsigned int timeout) {
    socket_ = NULL;
    timer_ = NULL;
    time_expired_ = false;
    secure_socket_ = new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(
        *io_service, *ssl_context);
    secure_socket_->set_verify_mode(ssl_verify_mode);
    SSL_set_tlsext_host_name(secure_socket_->native_handle(), host);
    init_timer(io_service, timeout);
}

void ApiSocket::init_timer(
    boost::asio::io_service *io_service, unsigned int timeout
) {
    if (timeout > 0) {
        timer_ = new boost::asio::deadline_timer(*io_service);
        timer_->expires_from_now(boost::posix_time::seconds(timeout));
        timer_->async_wait([this] (const boost::system::error_code& error) {
            if (!error) {
                time_expired_ = true;
                cancel();
            }
        });
    }
}

ApiSocket::~ApiSocket() {
    if (socket_) {
        delete socket_;
    }
    if (secure_socket_) {
        delete secure_socket_;
    }
}

boost::asio::ip::tcp::socket *ApiSocket::get_socket() {
    return socket_;
}

bool ApiSocket::is_secure() {
    return secure_socket_ != NULL;
}

boost::asio::ssl::stream<boost::asio::ip::tcp::socket>
    *ApiSocket::get_secure_socket() {
    return secure_socket_;
}

void ApiSocket::finish() {
    if (timer_) {
        boost::system::error_code ec;
        timer_->cancel(ec);
    }
    boost::system::error_code ec;
    if (socket_) {
        socket_->shutdown(
                boost::asio::ip::tcp::socket::shutdown_both);
        socket_->close(ec);
    } else {
        secure_socket_->shutdown();
        secure_socket_->lowest_layer().close(ec);
    }
}

void ApiSocket::cancel() {
    boost::system::error_code ec;
    if (socket_) {
        socket_->cancel(ec);
    } else {
        secure_socket_->lowest_layer().cancel(ec);
    }
}

}  // namespace apiclient
