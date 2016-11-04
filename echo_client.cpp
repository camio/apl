#include "channel.h"
#include "client.h"

#include <asio/ts/internet.hpp> // asio::tcp
#include <bbp/promise.h>
#include <iostream>

int main() {
  const asio::ip::tcp::endpoint serverAddress(asio::ip::tcp::v4(), 8000);

  asio::io_context context;
  client_connect(context, serverAddress).then([](channel c) {
    c.send("Hello\n")
     .then([c] { return c.send("world\n"); })
     .then([c] { return c.send("!!!\n"); });
  });
  context.run();
}
