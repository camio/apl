#ifndef CLIENT_INCLUDED
#define CLIENT_INCLUDED

#include <apl/tcp/channel.h>
#include <asio/ts/internet.hpp>   // asio::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <asio/ts/socket.hpp>     // asio::async_connect
#include <dpl/bbp/promise.h>
#include <stdexcept> // std::system_error

namespace apl {
namespace tcp {

inline dpl::bbp::promise<apl::tcp::channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress) {
  const std::shared_ptr<asio::ip::tcp::socket> socket(
      std::make_shared<asio::ip::tcp::socket>(io_context));
  return dpl::bbp::promise<apl::tcp::channel>([&](auto fulfill, auto reject) {
    asio::async_connect(
        *socket, std::vector<asio::ip::tcp::endpoint>{serverAddress},
        [fulfill, reject, socket](const asio::error_code &ec,
                                  const asio::ip::tcp::endpoint &endPoint) {
          if (!ec) {
            fulfill(apl::tcp::channel(std::move(*socket)));
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
}

#endif
