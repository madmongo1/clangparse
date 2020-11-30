cmake_minimum_required(VERSION 3.17)

include(FetchContent)

project(clangparse)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "FIND_LIBRARY_USE_LIB64_PATHS=${FIND_LIBRARY_USE_LIB64_PATHS}")

find_package(Clang)

FetchContent_Declare(fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG 7.1.3)
set(FMT_DOC OFF)
set(FMT_INSTALL OFF)
set(FMT_TEST OFF)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(clangparse ${src_files})
target_link_libraries(clangparse libclang fmt)
