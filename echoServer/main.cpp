#include <apl/tcp/channel.h>
#include <apl/tcp/server.h>
#include <asio/ts/internet.hpp> // asio::ip::tcp
#include <dplbbp_promise.h>
#include <iostream>

static dplbbp::promise<> readAndLog(apl::tcp::channel c) {
  return c.readUntil('\n')
      .then([](const std::string &msg) { std::cout << msg << std::endl; })
      .then([c] { return readAndLog(c); });
}

int main() {
  asio::io_context context;
  const asio::ip::tcp::endpoint listenAddress(asio::ip::tcp::v4(), 8000);

  try {
    // TODO: i don't like that creating a server can throw an exception. See if
    // there's another way to create a tcp acceptor that produces an error code
    // which I can pass on to the 'listen()' calls.
    apl::tcp::server s(context, listenAddress);
    s.listen().then(readAndLog,
                    [](std::exception_ptr e) -> dplbbp::promise<> {
                      try {
                        std::rethrow_exception(e);
                      } catch (std::system_error &e) {
                        std::cout << "Then Error: " << e.what() << std::endl;
                      }
                    });
  } catch (std::system_error &e) {
    std::cout << "Server Creation Error: " << e.what() << std::endl;
  }

  context.run();
}
