cmake_minimum_required(VERSION 3.20)
project(ImplicitStefanProblemMPI)

set(CMAKE_CXX_STANDARD 17)

# -funroll-loops
# -mtune=native -funroll-loops -ffast-math -ftree-vectorize -ftree-vectorizer-verbose=0
if (Debug)
    set(COMPILE_FLAGS "-O0 -g -Wall")
else()
    set(COMPILE_FLAGS "-O3 -Wall -Werror")
endif(Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

#set(HEADER_FILES

#)

set(SOURCE_FILES
        main.cpp
   )

# ${HEADER_FILES}
add_executable(ImplicitStefanProblemMPI ${SOURCE_FILES})

include_directories(base mesh basic_parabolic)

# MPI OMP linking + Basic utilities
add_subdirectory(base)
# Mesh template and MPI sync functions
add_subdirectory(mesh)
# Basic parabolic task solver
add_subdirectory(basic_parabolic)
# Catch2 tests
add_subdirectory(tests)

target_link_libraries(ImplicitStefanProblemMPI PRIVATE base mesh basic_parabolic)