## TODO
- Make the echo server keep logging whatever the client is sending. I think to
  do this properly, we'll need to implement the #3 functionality of promise.

```c++
static bbp::promise<> readAndLog(channel c) {
  c.read()
      .then([](const std::string &msg) { std::cout << msg << std::endl; })
      .then([c]() { return readAndLog(c); });
}
```
- Add a special message handler in the server which shuts down the connection
  when everything is done.
- Add promise<promise> returns to the promise lib and then fors the sequencing
  of the client by inserting return statements.
- See if the "completion token" could be used to generate a promise in
  'asio::async_read_until' as called in 'channel'.
- Figure out how to make this more general so it isn't always depending on '\0'
  based messages. That or somehow wrap that functionality in a layer on top.
- Make this into a CMake build.
- Make the server and the client into header/cpp files.
- Clear out and remove main.cpp.
- Make the server not have to outlive the promises it returns.
