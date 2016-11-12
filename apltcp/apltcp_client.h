#ifndef APLTCP_CLIENT_INCLUDED
#define APLTCP_CLIENT_INCLUDED

#include <asio/ts/internet.hpp>   // asio::tcp
#include <asio/ts/io_context.hpp> // asio::io_context

namespace dplbbp {
template <typename... Types> class promise;
}

namespace apltcp {
class channel;

dplbbp::promise<apltcp::channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress);
}

#endif
