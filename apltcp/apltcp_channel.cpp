#include <apltcp_channel.h>
#include <dplp_promise.h>
#include <stdexcept> // std::system_error

namespace apltcp {
channel::channel(asio::ip::tcp::socket socket)
    : d_socket(std::make_shared<asio::ip::tcp::socket>(std::move(socket))),
      d_read_buffer(std::make_shared<std::string>()) {}

dplp::Promise<> channel::send(std::string msg) const {
  return dplp::Promise<>([&msg, this](auto fulfill, auto reject) {
    const std::shared_ptr<std::string> write_buffer =
        std::make_shared<std::string>(std::move(msg));
    asio::async_write(*d_socket, asio::buffer(*write_buffer),
                      [ fulfill, reject, socket = d_socket, write_buffer ](
                          const std::error_code ec, const std::size_t length) {
                        if (!ec) {
                          fulfill();
                        } else {
                          reject(std::make_exception_ptr(std::system_error(ec)));
                        }
                      });
  });
}

dplp::Promise<std::string> channel::readUntil(char delim) const {
  return dplp::Promise<std::string>(
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
                reject(std::make_exception_ptr(std::system_error(ec)));
              }
            });
      });
}
}
