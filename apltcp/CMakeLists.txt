project(apltcp)

find_package(ASIO REQUIRED)

add_library(apltcp INTERFACE)
target_include_directories(apltcp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(apltcp INTERFACE asio)
