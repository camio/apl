cmake_minimum_required(VERSION 3.6)

project(apl)

if(NOT TARGET apl_echoClient)
  add_subdirectory(../apl/echoClient ${CMAKE_BINARY_DIR}/apl/echoClient)
endif()

if(NOT TARGET apl_echoServer)
  add_subdirectory(../apl/echoServer ${CMAKE_BINARY_DIR}/apl/echoServer)
endif()

if(NOT TARGET apl_tcp)
  add_subdirectory(../apl/tcp ${CMAKE_BINARY_DIR}/apl/echoServer)
endif()

add_custom_target(apl DEPENDS apl_echoClient apl_echoServer apl_tcp)
