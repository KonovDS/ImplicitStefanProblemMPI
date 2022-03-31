cmake_minimum_required(VERSION 3.20)
project(ImplicitStefanProblemMPI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

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

# Check for OMP
find_package(OpenMP REQUIRED)
# Check for MPI
find_package(MPI REQUIRED)
target_link_libraries(ImplicitStefanProblemMPI ${MPI_C_LIBRARIES})
include_directories("C:\\Program Files\\MPICH2\\include\\")

# UBUNTU MPICH PATH = "/usr/lib/x86_64-linux-gnu/mpich/include"
