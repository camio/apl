#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <asio/ts/internet.hpp>   // asio::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <asio/ts/socket.hpp>     // asio::async_connect
#include <bbp/promise.h>

#include "channel.h"

inline bbp::promise<channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress ) {
  const std::shared_ptr<asio::ip::tcp::socket> socket(
      std::make_shared<asio::ip::tcp::socket>(io_context));
  return bbp::promise<channel>([&](auto fulfill, auto reject) {
    asio::async_connect(
        *socket, std::vector<asio::ip::tcp::endpoint>{serverAddress},
        [fulfill, reject, socket](const asio::error_code &ec,
                                  const asio::ip::tcp::endpoint &endPoint) {
          if (!ec) {
            fulfill(channel(std::move(*socket)));
          } else {
            try {
              throw ec;
            } catch (...) {
              reject(std::current_exception());
            }
          }
        });
  });
}

#endif