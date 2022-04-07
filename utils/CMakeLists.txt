project(utils)

set(HEADER_FILES
        print.h
        progress.h
        utils.h
        )

set(SOURCE_FILES
        utils.cpp
        )


add_library(utils STATIC ${SOURCE_FILES} ${HEADER_FILES})

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(utils OpenMP::OpenMP_CXX)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(utils MPI::MPI_CXX)