cmake_minimum_required(VERSION 3.5.1)
project(lab11 C)

add_executable(${PROJECT_NAME} src/main.c src/knapsack.c src/item.c )
add_compile_options(-Werror -Wall -Wextra -Waddress -Warray-bounds -Wbuiltin-macro-redefined -Wswitch -Wunreachable-code -pedantic -pedantic-errors -std=c99)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
