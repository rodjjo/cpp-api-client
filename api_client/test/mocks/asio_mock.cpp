/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 */
#include "api_client/test/mocks/asio.hpp"


std::string boost::asio::ip::tcp::resolver::query::host_; // NOLINT
std::string boost::asio::ip::tcp::resolver::query::service_; // NOLINT
boost::asio::ip::tcp::resolver::iterator boost::asio::ip::tcp::resolver::iterator_; // NOLINT
boost::system::error_code boost::asio::ip::tcp::resolver::error_; // NOLINT
bool boost::asio::ip::tcp::resolver::resolve_called_ = false;

void boost::reset_mocks() {
    boost::asio::ip::tcp::resolver::query::host_ = std::string();
    boost::asio::ip::tcp::resolver::query::service_ = std::string();
    boost::asio::ip::tcp::resolver::error_ = 0;
    boost::asio::ip::tcp::resolver::resolve_called_ = false;
}
