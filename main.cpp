// There are three different executors that I'm aware of. I'm still not clear
// on what the differences are wrt. the standard.

#include <asio/thread_pool.hpp>   // An executor that runs on a specified number
                                  // of threads.
#include <asio/ts/executor.hpp>   // asio::system_context, asio::system_executor
#include <asio/ts/io_context.hpp> // asio::io_context

#include <iostream>

// io_context satisfies the ExecutionContext concept.
// system_context satisfies the ExecutionContext concept. (system_executor
// satisfies the Executor concept)
// thread_pool satisfies the ExecutionContext concept.


// async_result produces a completion handler for a given completion token and
// signature.
//
// async_completion uses async_result to get a completion_handler for its
// completion token and signature.
//
// associated_executor maps types to corresponding executors. Unless otherwise
// specialized, the system_executor is used.
//
// post uses 'associated_executor' on the 'completion_handler' provided by
// 'async_completion'.

// QUESTIONS FOR DESIGNERS
// - What is the meaning of posting something and *then* creating a
//   'system_context' and joining on it?

// TODO: WTF is 'std::make_service'? He's not using it anywhere. Can I make his
// tcp echo server example utilize it somehow?
// - I don't think so. The "service" classes are indexed by type and are
//   specifically designed for when you want no more than one instance of the
//   class living in an execution context. In the case of an echo server, we
//   may want to have one context running several echo servers that each are
//   bound to different ports. I'm not really sure *when* someone would
//   actually want this service functionality. There isn't a motivating
//   example. It seems like this is a way to add arbitrary crap to the
//   io_service storage which is suspect.
int main() {
  asio::io_context context;

  // Post a function using the executor in the first argument.
//  asio::post( context.get_executor(), [] { std::cout << "Here" << std::endl; } );

  // Post a function using the executor in 'context'.
  asio::post( context, [] { std::cout << "Here" << std::endl; } );

  // Post a function using using a 'system_executor'. Note that which executor
  // to be used is derived from the second argument.
//  asio::post( [] { std::cout << "Huh?" << std::endl; } );

  // Here we call post directly based on the executor. This is a low-level
  // function that shouldn't normall be used. We need to specify which
  // allocator we want. We generally want to use an allocator that is
  // already associated with the completion_handler which is derived from the
  // single argument. Usually this is going to be 'std::allocator<void>'.
  context.get_executor().post([] { std::cout << "Ah" << std::endl; },
                              std::allocator<void>());

  std::cout << "Hello world" << std::endl;

  context.run();
}
