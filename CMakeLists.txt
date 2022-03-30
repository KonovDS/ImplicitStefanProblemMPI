cmake_minimum_required(VERSION 3.6)
project(ImplicitStefanProblemMPI)

set(CMAKE_CXX_STANDARD 17)

#set(HEADER_FILES
#        mesh.h
#        )

set(SOURCE_FILES
        main.cpp
        )
#                                                      ${HEADER_FILES}
add_executable(ImplicitStefanProblemMPI ${SOURCE_FILES})

include_directories(mesh)
add_subdirectory(mesh)

target_link_libraries(ImplicitStefanProblemMPI mesh)

add_subdirectory(tests)

