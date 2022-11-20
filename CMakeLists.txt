cmake_minimum_required(VERSION 3.14)
project(KursovaAK)

set(CMAKE_CXX_STANDARD 14)

include(translator/CMakeLists.txt)
include(services/CMakeLists.txt)
include(simulator/CMakeLists.txt)
include(tests/CMakeLists.txt)

add_executable(
        KursovaAK
        main.cpp
        ${myApp_SOURCES})

include_directories(${myApp_INCLUDES})
