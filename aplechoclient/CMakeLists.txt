cmake_minimum_required(VERSION 3.6)
project(aplechoclient)

cmsi_importp(apltcp)

add_executable(aplechoclient aplechoclient.m.cpp)
target_link_libraries(aplechoclient apltcp ASIO::ASIO dplp)
