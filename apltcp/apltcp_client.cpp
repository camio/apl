#include <apltcp_client.h>

#include <apltcp_channel.h>
#include <asio/ts/socket.hpp>     // asio::async_connect
#include <dplp_promise.h>
#include <stdexcept> // std::system_error

namespace apltcp {

dplp::Promise<apltcp::channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress) {
  const std::shared_ptr<asio::ip::tcp::socket> socket(
      std::make_shared<asio::ip::tcp::socket>(io_context));
  return dplp::Promise<apltcp::channel>([&](auto fulfill, auto reject) {
    asio::async_connect(
        *socket, std::vector<asio::ip::tcp::endpoint>{serverAddress},
        [fulfill, reject, socket](const asio::error_code &ec,
                                  const asio::ip::tcp::endpoint &endPoint) {
          if (!ec) {
            fulfill(apltcp::channel(std::move(*socket)));
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
}
