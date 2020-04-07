cmake_minimum_required(VERSION 3.5)

project(aps LANGUAGES C)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.c
)

add_executable(desafio1 ${SOURCES})
