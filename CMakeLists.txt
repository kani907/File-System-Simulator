cmake_minimum_required(VERSION 3.12)
project(FileSaver)
include(FetchContent)
add_subdirectory(tests)
add_subdirectory(src)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()