cmake_minimum_required(VERSION 3.6)
project(ImplicitStefanProblemMPI)

set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        ui.h
        )

set(SOURCE_FILES
        main.cpp
        ui.cpp)

add_executable(ImplicitStefanProblemMPI ${SOURCE_FILES} ${HEADER_FILES})

include_directories(mesh)
add_subdirectory(mesh)

target_link_libraries(ImplicitStefanProblemMPI mesh)

add_subdirectory(tests)

