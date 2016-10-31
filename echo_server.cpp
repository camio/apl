#include "channel.h"
#include "server.h"

#include <asio/ts/internet.hpp> // asio::ip::tcp
#include <bbp/promise.h>
#include <iostream>

static bbp::promise<> readAndLog(channel c) {
  return c.readUntil('\0')
      .then([](const std::string &msg) {
        std::cout << msg << std::endl;
      })
      .then([c] {
        return readAndLog(c);
      });
}

int main() {
  asio::io_context context;
  const asio::ip::tcp::endpoint listenAddress(asio::ip::tcp::v4(), 8000);

  server s(context, listenAddress);
  s.listen().then(readAndLog);

  context.run();
}
