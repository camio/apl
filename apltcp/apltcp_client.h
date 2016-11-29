#ifndef APLTCP_CLIENT_INCLUDED
#define APLTCP_CLIENT_INCLUDED

#include <asio/ts/internet.hpp>   // asio::tcp
#include <asio/ts/io_context.hpp> // asio::io_context

namespace dplp {
template <typename... Types> class Promise;
}

namespace apltcp {
class channel;

dplp::Promise<apltcp::channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress);
}

#endif
