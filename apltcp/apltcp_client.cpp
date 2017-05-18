#include <apltcp_client.h>

#include <apltcp_channel.h>
#include <asio/ts/socket.hpp>     // asio::async_connect
#include <dplp_promise.h>
#include <stdexcept> // std::system_error

namespace apltcp {

dplp::Promise<apltcp::channel>
client_connect(asio::io_context &io_context,
               const asio::ip::tcp::endpoint &serverAddress) {
  const std::shared_ptr<asio::ip::tcp::socket> socket(
      std::make_shared<asio::ip::tcp::socket>(io_context));
  return dplp::Promise<apltcp::channel>([&](auto fulfill, auto reject) {
    asio::async_connect(
        *socket, std::vector<asio::ip::tcp::endpoint>{serverAddress},
        [fulfill, reject, socket](const asio::error_code &ec,
                                  const asio::ip::tcp::endpoint &endPoint) {
          if (!ec) {
            fulfill(apltcp::channel(std::move(*socket)));
          } else {
            reject(std::make_exception_ptr(std::system_error(ec)));
          }
        });
  });
}
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
