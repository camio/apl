#include <apltcp_channel.h>
#include <apltcp_server.h>
#include <asio/ts/internet.hpp> // asio::ip::tcp
#include <dplp_promise.h>
#include <iostream>

static dplp::Promise<> readAndLog(apltcp::channel c) {
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
    apltcp::server s(context, listenAddress);
    s.listen().then(readAndLog,
                    [](std::exception_ptr e) -> dplp::Promise<> {
                      try {
                        std::rethrow_exception(e);
                      } catch (std::system_error &e) {
                        std::cout << "Then Error: " << e.what() << std::endl;
                      }
                      return dplp::makeFulfilledPromise<>();
                    });
  } catch (std::system_error &e) {
    std::cout << "Server Creation Error: " << e.what() << std::endl;
  }

  context.run();
}

// ----------------------------------------------------------------------------
// Copyright 2017 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
