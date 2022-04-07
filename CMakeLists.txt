cmake_minimum_required(VERSION 3.20)
project(ImplicitStefanProblemMPI)

set(CMAKE_CXX_STANDARD 17)

# -pedantic -lm -O3 -funroll-loops
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#set(HEADER_FILES

#)

set(SOURCE_FILES
        main.cpp
   )

# ${HEADER_FILES}
add_executable(ImplicitStefanProblemMPI ${SOURCE_FILES} )

include_directories(mesh)
add_subdirectory(mesh)
target_link_libraries(ImplicitStefanProblemMPI mesh)

include_directories(basic_parabolic)
add_subdirectory(basic_parabolic)
target_link_libraries(ImplicitStefanProblemMPI basic_parabolic)

include_directories(utils)
add_subdirectory(utils)
target_link_libraries(ImplicitStefanProblemMPI utils)

# Tests
add_subdirectory(tests)

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(ImplicitStefanProblemMPI OpenMP::OpenMP_CXX)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(ImplicitStefanProblemMPI MPI::MPI_CXX)