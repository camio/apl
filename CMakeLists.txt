cmake_minimum_required(VERSION 3.6)
project(apl)

include(cmsi_import)

cmsi_import(dpl)

find_package(ASIO REQUIRED)

cmsi_importp(aplechoclient)
cmsi_importp(aplechoserver)
cmsi_importp(apltcp)

add_custom_target(apl DEPENDS
  aplechoclient
  aplechoserver
  apltcp
)
