#ifndef CHANNEL_H_INCLUDED
#define CHANNEL_H_INCLUDED

#include <asio/ts/buffer.hpp>   // asio::dynamic, asio::read_until
#include <asio/ts/internet.hpp> // asio::tcp::endpoint
#include <bbp/promise.h>
#include <stdexcept> // std::system_error
#include <string>
#include <utility> // std::shared_ptr

// This class implements a mechanism whereby strings can be sent and read from
// an open TCP connection.
class channel {
  std::shared_ptr<asio::ip::tcp::socket> d_socket;
  std::shared_ptr<std::string> d_read_buffer;

public:
  // Create a new 'channel' object using the specified 'socket'.
  channel(asio::ip::tcp::socket socket)
      : d_socket(std::make_shared<asio::ip::tcp::socket>(std::move(socket))),
        d_read_buffer(std::make_shared<std::string>()) {}

  // Send the specified 'msg' over the TCP connection followed by the '\0'
  // character. Return a promise that is fulfilled when the operation is
  // complete or rejected with a 'std::error_code' when the operation fails.
  bbp::promise<> send(std::string msg) const {
    return bbp::promise<>([&msg, this](auto fulfill, auto reject) {
      const std::shared_ptr<std::string> write_buffer =
          std::make_shared<std::string>(std::move(msg));
      asio::async_write(*d_socket, asio::buffer(*write_buffer), [
        fulfill, reject, socket = d_socket, write_buffer
      ](const std::error_code ec, const std::size_t length) {
        if (!ec) {
          fulfill();
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

  // Read bytes from the TCP connection until the specified 'delim' delimiter
  // character is reached. Return a promise that is fulfilled with the
  // characters read, not including the delimiter, when the operation is
  // complete or rejected with a 'std::error_code' when the operation fails.
  bbp::promise<std::string> readUntil(char delim) const {
    return bbp::promise<std::string>(
        [ delim, socket = d_socket, read_buffer = d_read_buffer ](auto fulfill,
                                                                  auto reject) {
          asio::async_read_until(
              *socket, asio::dynamic_buffer(*read_buffer), delim,
              [read_buffer, socket, fulfill, reject](const std::error_code ec,
                                                     const std::size_t length) {
                if (!ec) {
                  std::string dataPiece = read_buffer->substr(0, length - 1);
                  read_buffer->erase(0, length);
                  fulfill(std::move(dataPiece));
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
