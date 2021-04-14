cmake_minimum_required (VERSION 2.8.11)


project (client)

add_executable (client main_fm.cpp filemanager.cpp filemanager.h filemanager_stub.cpp filemanager_stub.h utils.cpp utils.h)

target_link_libraries(client pthread)


project (server)

add_executable (server server.cpp filemanager.cpp filemanager.h filemanager_imp.cpp filemanager_imp.h utils.cpp utils.h)

target_link_libraries(server pthread)