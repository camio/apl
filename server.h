#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include <asio/ts/internet.hpp>   // asio::ip::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <bbp/promise.h>
#include <iostream>
#include <stdexcept> // std::system_error

#include "channel.h"

class server {
  std::shared_ptr<asio::ip::tcp::acceptor> d_acceptor;

public:
  server(asio::io_context &io_context, asio::ip::tcp::endpoint listenEndpoint)
      : d_acceptor(std::make_shared<asio::ip::tcp::acceptor>(io_context,
                                                             listenEndpoint)) {}

  bbp::promise<channel> listen() {
    return bbp::promise<channel>([this](auto fulfill, auto reject) {
      std::unique_ptr<asio::ip::tcp::socket> socket =
          std::make_unique<asio::ip::tcp::socket>(
              d_acceptor->get_executor().context());
      d_acceptor->async_accept(*socket, [
        acceptor = d_acceptor, socket = std::move(socket), fulfill, reject
      ](std::error_code ec) {
        if (!ec) {
          fulfill(channel(std::move(*socket)));
        } else {
          std::cout << "Error on async_accept" << std::endl;
          try {
            throw std::system_error(ec);
          } catch (...) {
            reject(std::current_exception());
          }
        }
      });
    });
  }
};

#endif
