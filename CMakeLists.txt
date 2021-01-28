cmake_minimum_required(VERSION 3.17)
project(cub C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cub
        cub.h
        parser.c main.c parse_rgb.c main_fc.c)
