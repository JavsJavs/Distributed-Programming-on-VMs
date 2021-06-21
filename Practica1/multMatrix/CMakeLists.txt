cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS -pthread)

project (multMatrix)
add_executable (client main_multMatrix.cpp multmatrix.cpp multmatrix.h utils.h utils.cpp multMatrix_stub.h multMatrix_stub.cpp matrix_func.h matrix_func.cpp)
add_executable (server server.cpp multmatrix.cpp multmatrix.h utils.h utils.cpp multMatrix_imp.h multMatrix_imp.cpp matrix_func.h matrix_func.cpp)
