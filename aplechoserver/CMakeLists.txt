cmake_minimum_required(VERSION 3.6)
project(aplechoserver)

if(NOT TARGET apltcp)
  add_subdirectory(../apltcp ${CMAKE_BINARY_DIR}/apl/apltcp)
endif()

if(NOT TARGET dplp)
  add_subdirectory(../../dpl/dplp ${CMAKE_BINARY_DIR}/dpl/dplp)
endif()

find_package(ASIO REQUIRED)

add_executable(aplechoserver aplechoserver.m.cpp)
target_link_libraries(aplechoserver apltcp asio dplp)
