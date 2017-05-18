#include <apltcp_server.h>

#include <apltcp_channel.h>
#include <dplp_promise.h>
#include <iostream>
#include <stdexcept> // std::system_error

namespace apltcp {
server::server(asio::io_context &io_context,
               asio::ip::tcp::endpoint listenEndpoint)
    : d_acceptor(std::make_shared<asio::ip::tcp::acceptor>(io_context,
                                                           listenEndpoint)) {}

dplp::Promise<apltcp::channel> server::listen() {
  return dplp::Promise<apltcp::channel>([this](auto fulfill, auto reject) {
    std::unique_ptr<asio::ip::tcp::socket> socket_up =
        std::make_unique<asio::ip::tcp::socket>(
            d_acceptor->get_executor().context());
    // Note that we need to extract the pointer in `socket_up` before we make
    // the `async_accept` call because `socket_up` is modified by the
    // `std::move` call in the capture. Evaluation order of the argument
    // expressions is unspecified.
    asio::ip::tcp::socket *const socket_p = socket_up.get();
    d_acceptor->async_accept(*socket_p, [
      acceptor = d_acceptor, socket = std::move(socket_up), fulfill, reject
    ](std::error_code ec) {
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
