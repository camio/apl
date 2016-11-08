# apl: ASIO Promise Library

**PURPOSE:** Provide a demonstration of promises using ASIO

- `channel.h`: TCP channel for communication
- `client.h`: Function to connect to a TCP server
- `echo_client.h`: Example "echo" client
- `echo_server.h`: Example "echo" server
- `server.h`: Assets for providing a TCP server

## Building
This library can be built with `make`. A checkout of the ASIO library is expected to be parallel to this repository.

## Notes
Note that I'm not using the `<asio/ts/netfwd.hpp>` header because it does not
forward declare types within `tcp` such as `asio::ip::tcp::acceptor`.

## TODO
- Reorganize
  apw/        (ASIO promise wrapper)
    apwtcp/   (APW's TCP library)
    apwtcpec/ (APW TCP echo client)
    apwtcpes/ (APW TCP echo server)
- Try writing an example app which uses protobuf to communicate messages back
  and forth.
- Add a special message handler in the server which shuts down the connection
  when everything is done.
- Provide an example where exceptions are captured and handled.
- See if the "completion token" could be used to generate a promise in
  'asio::async_read_until' as called in 'channel'.
- Make this into a CMake build.
- Make the server and the client into header/cpp files.
- Clear out and remove main.cpp.
- Make the server not have to outlive the promises it returns. (Does it really
  have to?)
- Create a special completion handler such that 'asio::post' returns a promise.
