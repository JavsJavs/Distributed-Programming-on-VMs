cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS -pthread)

project (fileManager)
add_executable (server server.cpp file_func.h file_func.cpp filemanager_imp.cpp filemanager_imp.h filemanager.cpp filemanager.h utils.h utils.cpp )
add_executable (client client.cpp file_func.h file_func.cpp filemanager_stub.cpp filemanager_stub.h  filemanager.cpp filemanager.h utils.h utils.cpp)