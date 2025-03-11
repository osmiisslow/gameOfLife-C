cmake_minimum_required(VERSION 3.31)
project(gameOfLife C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-lraylib -lGL -lm -lpthread -ldl -lrt -lX11")

include_directories(.)

add_executable(gameOfLife
        main.c
        logic.h)
