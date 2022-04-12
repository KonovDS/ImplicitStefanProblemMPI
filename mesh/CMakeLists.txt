project(mesh)

set(HEADER_FILES
        mesh.h
        mpi_mesh.h
   )

set(SOURCE_FILES
       mesh.cpp
   )


add_library(mesh STATIC ${SOURCE_FILES} ${HEADER_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

target_link_libraries(mesh base)

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(mesh OpenMP::OpenMP_CXX)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(mesh MPI::MPI_CXX)