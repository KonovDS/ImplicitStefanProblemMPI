add_executable(Catch_tests_run mesh.cpp omp_mpi.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
target_link_libraries(Catch_tests_run mesh)

find_package(MPI REQUIRED)
target_link_libraries(Catch_tests_run ${MPI_C_LIBRARIES})
include_directories("C:\\Program Files\\MPICH2\\include\\")
