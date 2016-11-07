cmake_minimum_required(VERSION 3.6)
project(apl_echoServer)

if(NOT TARGET apl_tcp)
  add_subdirectory(../../apl/tcp ${CMAKE_BINARY_DIR}/apl/tcp)
endif()

if(NOT TARGET dpl_bbp)
  add_subdirectory(../../dpl/bbp ${CMAKE_BINARY_DIR}/dpl/bbp)
endif()

find_package(ASIO REQUIRED)

add_executable(apl_echoServer main.cpp)
target_link_libraries(apl_echoServer apl_tcp asio dpl_bbp)
