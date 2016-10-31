# asio-promise-example

**PURPOSE:** Provide a demonstration of promises using ASIO

- `channel.h`: TCP channel for communication
- `client.h`: Function to connect to a TCP server
- `echo_client.h`: Example "echo" client
- `echo_server.h`: Example "echo" server
- `server.h`: Assets for providing a TCP server

## Building
This library can be built with `make`. A checkout of the ASIO library is expected to be parallel to this repository.

## TODO
- Add a special message handler in the server which shuts down the connection
  when everything is done.
- Capture exceptions and handle them
- See if the "completion token" could be used to generate a promise in
  'asio::async_read_until' as called in 'channel'.
- Make this into a CMake build.
- Make the server and the client into header/cpp files.
- Clear out and remove main.cpp.
- Make the server not have to outlive the promises it returns. (Does it really
  have to?)
