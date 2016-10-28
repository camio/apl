#ifndef CHANNEL_H_INCLUDED
#define CHANNEL_H_INCLUDED

#include <asio/ts/buffer.hpp>   // asio::dynamic, asio::read_until
#include <asio/ts/internet.hpp> // asio::tcp::endpoint
#include <bbp/promise.h>
#include <iostream>
#include <string>
#include <utility> // std::shared_ptr

class channel {
  std::shared_ptr<asio::ip::tcp::socket> d_socket;
  std::shared_ptr<std::string> d_read_buffer;

public:
  channel(asio::ip::tcp::socket socket)
      : d_socket(std::make_shared<asio::ip::tcp::socket>(std::move(socket))),
        d_read_buffer(std::make_shared<std::string>()) {}

  bbp::promise<> send(std::string msg) const {
    return bbp::promise<>([&msg, this](auto fulfill, auto reject) {
      msg += '\0';
      const std::shared_ptr<std::string> write_buffer =
          std::make_shared<std::string>(std::move(msg));
      asio::async_write(
          *d_socket, asio::buffer(*write_buffer),
          [ fulfill, reject, socket = d_socket,
            write_buffer ](const std::error_code ec, const std::size_t length) {
            if (!ec) {
              fulfill();
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
  bbp::promise<std::string> read() const {
    return bbp::promise<std::string>(
        [ socket = d_socket, read_buffer = d_read_buffer ](auto fulfill,
                                                           auto reject) {
          asio::async_read_until(
              *socket, asio::dynamic_buffer(*read_buffer), '\0',
              [read_buffer, fulfill, reject, socket](const std::error_code ec,
                                                     const std::size_t length) {
                if (!ec) {
                  fulfill(read_buffer->substr(0, length - 1));
                  read_buffer->erase(0, length);
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
};

#endif
