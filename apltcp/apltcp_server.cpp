#include <apltcp_server.h>

#include <apltcp_channel.h>
#include <dplbbp_promise.h>
#include <iostream>
#include <stdexcept> // std::system_error

namespace apltcp {
server::server(asio::io_context &io_context,
               asio::ip::tcp::endpoint listenEndpoint)
    : d_acceptor(std::make_shared<asio::ip::tcp::acceptor>(io_context,
                                                           listenEndpoint)) {}

dplbbp::promise<apltcp::channel> server::listen() {
  return dplbbp::promise<apltcp::channel>([this](auto fulfill, auto reject) {
    std::unique_ptr<asio::ip::tcp::socket> socket =
        std::make_unique<asio::ip::tcp::socket>(
            d_acceptor->get_executor().context());
    d_acceptor->async_accept(*socket, [
      acceptor = d_acceptor, socket = std::move(socket), fulfill, reject
    ](std::error_code ec) {
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
