project(apl_tcp)

find_package(ASIO REQUIRED)

add_library(apl_tcp INTERFACE)
target_include_directories(apl_tcp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_link_libraries(apl_tcp INTERFACE asio)
