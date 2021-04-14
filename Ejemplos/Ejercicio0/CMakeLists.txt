cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server utils.h utils.cpp server.cpp)

project(client LANGUAGES CXX)
add_executable(client utils.h utils.cpp cliente.cpp)