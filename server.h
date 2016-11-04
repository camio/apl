#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include <asio/ts/internet.hpp>   // asio::ip::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <bbp/promise.h>
#include <stdexcept> // std::system_error

#include "channel.h"

class server {
  asio::ip::tcp::acceptor d_acceptor;
  asio::ip::tcp::socket d_socket;

public:
  server(asio::io_context &io_context, asio::ip::tcp::endpoint listenEndpoint)
      : d_acceptor(io_context, listenEndpoint), d_socket(io_context) {}

  bbp::promise<channel> listen() {
    return bbp::promise<channel>([this](auto fulfill, auto reject) {
      d_acceptor.async_accept(d_socket,
                              [this, fulfill, reject](std::error_code ec) {
                                if (!ec) {
                                  fulfill(channel(std::move(this->d_socket)));
                                } else {
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
