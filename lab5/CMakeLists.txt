cmake_minimum_required(VERSION 3.5.1)
project(lab5 C)

set(SRC src/main.c src/bit_stream.c src/tree.c src/code.c
        src/huffman.c src/queue.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
