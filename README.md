## TODO
- Add a special message handler in the server which shuts down the connection
  when everything is done.
- See if the "completion token" could be used to generate a promise in
  'asio::async_read_until' as called in 'channel'.
- Make this into a CMake build.
- Make the server and the client into header/cpp files.
- Clear out and remove main.cpp.
- Make the server not have to outlive the promises it returns. (Does it really
  have to?)
