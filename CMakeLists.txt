project(ACT_TP3)

cmake_minimum_required(VERSION 2.8)

include_directories(.)

set(CMAKE_C_FLAGS "-pedantic -Werror -Wall -m32 -g")

file(GLOB_RECURSE source
    header.h
    main.c
    palette.h
    palette.c
    image.h
    image.c
    image_reader.h
    image_reader.c
    )

add_executable(palette ${source})

