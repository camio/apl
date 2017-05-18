#include <apltcp_channel.h>
#include <apltcp_client.h>
#include <asio/ts/internet.hpp> // asio::tcp
#include <dplp_promise.h>
#include <iostream>

int main() {
  const asio::ip::tcp::endpoint serverAddress(asio::ip::tcp::v4(), 8000);

  asio::io_context context;
  apltcp::client_connect(context, serverAddress)
      .then([](apltcp::channel c) {
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
