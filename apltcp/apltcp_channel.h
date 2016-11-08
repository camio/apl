#ifndef CHANNEL_INCLUDED
#define CHANNEL_INCLUDED

#include <asio/ts/buffer.hpp>   // asio::dynamic, asio::read_until
#include <asio/ts/internet.hpp> // asio::tcp::endpoint, asio::ip::tcp::socket
#include <string>
#include <utility> // std::shared_ptr

namespace dplbbp {
template <typename... Types> class promise;
}

namespace apltcp {

// This class implements a mechanism whereby strings can be sent and read from
// an open TCP connection.
class channel {
  std::shared_ptr<asio::ip::tcp::socket> d_socket;
  std::shared_ptr<std::string> d_read_buffer;

public:
  // Create a new 'channel' object using the specified 'socket'.
  channel(asio::ip::tcp::socket socket);

  // Send the specified 'msg' over the TCP connection followed by the '\0'
  // character. Return a promise that is fulfilled when the operation is
  // complete or rejected with a 'std::error_code' when the operation fails.
  dplbbp::promise<> send(std::string msg) const;

  // Read bytes from the TCP connection until the specified 'delim' delimiter
  // character is reached. Return a promise that is fulfilled with the
  // characters read, not including the delimiter, when the operation is
  // complete or rejected with a 'std::error_code' when the operation fails.
  dplbbp::promise<std::string> readUntil(char delim) const;
};

}

#endif
