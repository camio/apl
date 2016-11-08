cmake_minimum_required(VERSION 3.6)
project(apl_echoServer)

if(NOT TARGET apl_tcp)
  add_subdirectory(../../apl/tcp ${CMAKE_BINARY_DIR}/apl/tcp)
endif()

if(NOT TARGET dplbbp)
  add_subdirectory(../../dplbbp ${CMAKE_BINARY_DIR}/dplbbp)
endif()

find_package(ASIO REQUIRED)

add_executable(apl_echoServer main.cpp)
target_link_libraries(apl_echoServer apl_tcp asio dplbbp)
