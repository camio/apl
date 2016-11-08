#include <apl/tcp/channel.h>
#include <apl/tcp/client.h>
#include <asio/ts/internet.hpp> // asio::tcp
#include <dplbbp_promise.h>
#include <iostream>

int main() {
  const asio::ip::tcp::endpoint serverAddress(asio::ip::tcp::v4(), 8000);

  asio::io_context context;
  apl::tcp::client_connect(context, serverAddress)
      .then([](apl::tcp::channel c) {
        return c.send("Hello\n")
            .then([c] { return c.send("world\n"); })
            .then([c] { return c.send("!!!\n"); });
      })
      .then([] {},
            [](std::exception_ptr e) {
              try {
                std::rethrow_exception(e);
              } catch (std::system_error &e) {
                std::cout << "Error: " << e.what() << std::endl;
              }
            });
  context.run();
}
