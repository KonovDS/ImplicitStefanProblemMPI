project(base)

set(HEADER_FILES
        print.h
        progress.h
        utils.h
        timer.h)

set(SOURCE_FILES
        utils.cpp
        timer.cpp)


add_library(base STATIC ${SOURCE_FILES} ${HEADER_FILES})

# MPI and OpenMP
find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)
target_link_libraries(base PUBLIC OpenMP::OpenMP_CXX MPI::MPI_CXX)
