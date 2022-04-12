project(basic_parabolic)

set(HEADER_FILES
    basic_parabolic.h
   )

set(SOURCE_FILES
    basic_parabolic.cpp
   )


add_library(basic_parabolic STATIC ${SOURCE_FILES} ${HEADER_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

target_link_libraries(basic_parabolic PRIVATE mesh base)