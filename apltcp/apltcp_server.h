#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include <asio/ts/internet.hpp>   // asio::ip::tcp
#include <asio/ts/io_context.hpp> // asio::io_context
#include <memory>                 // std::shared_ptr

namespace dplbbp {
template <typename... Types> class promise;
}

namespace apltcp {

class channel;

class server {
  std::shared_ptr<asio::ip::tcp::acceptor> d_acceptor;

public:
  server(asio::io_context &io_context, asio::ip::tcp::endpoint listenEndpoint);

  dplbbp::promise<apltcp::channel> listen();
};
}

#endif
