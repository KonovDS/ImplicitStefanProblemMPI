project(mesh)

set(HEADER_FILES
        mesh.h
        )

set(SOURCE_FILES
        mesh.cpp
        )

add_library(mesh STATIC ${SOURCE_FILES} ${HEADER_FILES})