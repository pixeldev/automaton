cmake_minimum_required(VERSION 3.29)
project(third_practice C)

set(CMAKE_C_STANDARD 23)

add_executable(third_practice main.c
        determinist.c
        string.c
        string.h
        int_array.c
        int_array.h
        char_array.c
        char_array.h
        transition.c
        transition.h
        automaton.c
        automaton.h
        determinist.h)
