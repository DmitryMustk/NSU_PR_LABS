cmake_minimum_required(VERSION 3.5.1)
project(lab6-0 C)

add_executable(${PROJECT_NAME} src/main.c src/node.c src/memory.c src/avlTree.c)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)


