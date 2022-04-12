set(TESTS_FILES
        test_omp_mpi.cpp
        test_mesh.cpp
        test_mpi_mesh.cpp
)

set(CATCH_HELPERS
        lib/catch_main.cpp
        lib/mpi_helpers.h
        lib/catch.hpp
        )

add_executable(Catch_tests_run ${CATCH_HELPERS} ${TESTS_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

target_link_libraries(Catch_tests_run PRIVATE mesh base)