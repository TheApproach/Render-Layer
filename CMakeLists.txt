cmake_minimum_required(VERSION 3.28)
project(render)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)
include_directories(tests)

add_executable(render
        container.h
        main.cpp
        node.h
        stream.h
        xml.h
        main.cpp
        streamtype.h
        render.h
)

add_executable(render_test
        tests/doctest.h
        tests/test.cpp
)
