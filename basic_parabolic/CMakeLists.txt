project(basic_parabolic)

set(HEADER_FILES
    basic_parabolic.h
   )

set(SOURCE_FILES
    basic_parabolic.cpp
   )


add_library(basic_parabolic STATIC ${SOURCE_FILES} ${HEADER_FILES})

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(basic_parabolic OpenMP::OpenMP_CXX)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(basic_parabolic MPI::MPI_CXX)