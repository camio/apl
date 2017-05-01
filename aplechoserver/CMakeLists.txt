cmake_minimum_required(VERSION 3.6)
project(aplechoserver)

cmsi_importp(apltcp)

add_executable(aplechoserver aplechoserver.m.cpp)
target_link_libraries(aplechoserver apltcp ASIO::ASIO dplp)
