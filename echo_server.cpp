#include "channel.h"
#include "server.h"

#include <asio/ts/internet.hpp> // asio::ip::tcp
#include <bbp/promise.h>
#include <iostream>

int main() {
  asio::io_context context;
  asio::ip::tcp::endpoint listenAddress(asio::ip::tcp::v4(), 8000);

  server s(context, listenAddress);

  s.listen().then([](channel c) {
    return c.read().then([](const std::string &input) {
      std::cout << "Received: " << input << std::endl;
    });
  });

  context.run();
}
