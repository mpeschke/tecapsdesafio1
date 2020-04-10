cmake_minimum_required(VERSION 3.5)

project(tecdesafioaps LANGUAGES C)

file(GLOB_RECURSE SOURCES
    src/*.c
)

add_executable(tecdesafioaps ${SOURCES})

enable_testing()

add_subdirectory(test)
