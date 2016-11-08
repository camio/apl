cmake_minimum_required(VERSION 3.6)
project(aplechoclient)

if(NOT TARGET apltcp)
  add_subdirectory(../apltcp ${CMAKE_BINARY_DIR}/apl/tcp)
endif()

if(NOT TARGET dplbbp)
  add_subdirectory(../../dpl/dplbbp ${CMAKE_BINARY_DIR}/dpl/dplbbp)
endif()

find_package(ASIO REQUIRED)

add_executable(aplechoclient aplechoclient.m.cpp)
target_link_libraries(aplechoclient apltcp asio dplbbp)
