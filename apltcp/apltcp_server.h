#ifndef APLTCP_SERVER_INCLUDED
#define APLTCP_SERVER_INCLUDED

#include <asio/ts/internet.hpp>   // asio::ip::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <memory>                 // std::shared_ptr

namespace dplp {
template <typename... Types> class Promise;
}

namespace apltcp {

class channel;

class server {
  std::shared_ptr<asio::ip::tcp::acceptor> d_acceptor;

public:
  server(asio::io_context &io_context, asio::ip::tcp::endpoint listenEndpoint);

  dplp::Promise<apltcp::channel> listen();
};
}

#endif
