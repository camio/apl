cmake_minimum_required(VERSION 3.6)
project(apltcp)

add_library(apltcp
  apltcp_channel.h
  apltcp_channel.cpp
  apltcp_client.h
  apltcp_client.cpp
  apltcp_server.h
  apltcp_server.cpp
)
target_include_directories(apltcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(apltcp ASIO::ASIO dplp)
