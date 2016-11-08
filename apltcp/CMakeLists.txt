cmake_minimum_required(VERSION 3.6)
project(apltcp)

if(NOT TARGET dplbbp)
  add_subdirectory(../../dpl/dplbbp ${CMAKE_BINARY_DIR}/dpl/dplbbp)
endif()

find_package(ASIO REQUIRED)

add_library(apltcp apltcp_channel.cpp apltcp_client.cpp apltcp_server.cpp)
target_include_directories(apltcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(apltcp asio dplbbp)
