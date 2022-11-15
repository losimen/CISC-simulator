cmake_minimum_required(VERSION 3.14)
project(KursovaAK)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        hello_test
        assember_test.cpp fileworker.cpp fileworker.h syntaxanalyzer.cpp syntaxanalyzer.h int24_t.cpp int24_t.h info.h
        commands.cpp commands.h codegenerator.cpp codegenerator.h)

add_executable(
        KursovaAK
        main.cpp
        fileworker.cpp fileworker.h syntaxanalyzer.cpp syntaxanalyzer.h int24_t.cpp int24_t.h info.h commands.cpp commands.h codegenerator.cpp codegenerator.h)

target_link_libraries(
        hello_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
