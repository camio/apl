cmake_minimum_required(VERSION 3.6)

project(apl)

if(NOT TARGET aplechoclient)
  add_subdirectory(aplechoclient ${CMAKE_BINARY_DIR}/apl/aplechoclient)
endif()

if(NOT TARGET aplechoserver)
  add_subdirectory(aplechoserver ${CMAKE_BINARY_DIR}/apl/aplechoserver)
endif()

if(NOT TARGET apltcp)
  add_subdirectory(apltcp ${CMAKE_BINARY_DIR}/apl/aplechoserver)
endif()

add_custom_target(apl DEPENDS
  aplechoclient
  aplechoserver
  apltcp
)
