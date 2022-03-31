project(mesh)

set(HEADER_FILES
        mesh.h
        mpi_mesh.h
   )

set(SOURCE_FILES
       mesh.cpp
   )


add_library(mesh STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(MPI REQUIRED)
target_link_libraries(mesh ${MPI_C_LIBRARIES})
include_directories("C:\\Program Files\\MPICH2\\include\\")