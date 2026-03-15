cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 99)

# Здесь перечислены ВСЕ .c файлы!
add_executable(untitled
        main.c
        vector.c
        typeinfo.c
        tests.c
)