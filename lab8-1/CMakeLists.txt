cmake_minimum_required(VERSION 3.5.1)
project(lab8-1 C)

set(SRC src/main.c src/graph.c src/graph.h src/constants.h src/prim_info.c src/prim_info.h)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
