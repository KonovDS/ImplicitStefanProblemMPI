add_executable(Catch_tests_run omp_mpi.cpp mesh.cpp mpi_mesh.cpp main.cpp print.h mpi_helpers.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

target_link_libraries(Catch_tests_run mesh)

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(Catch_tests_run OpenMP::OpenMP_CXX)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(Catch_tests_run MPI::MPI_CXX)