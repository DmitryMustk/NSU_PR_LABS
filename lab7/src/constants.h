#ifndef LAB7_CONSTANTS_H
#define LAB7_CONSTANTS_H
typedef enum error_code {
    no_error = 0,
    other_error,
    bad_number_of_lines,
    bad_number_of_vertices,
    bad_number_of_edges,
    bad_vertex,
    impossible_to_sort,
} error_code;

typedef enum colors {
    white,
    gray,
    black,
} colors;

#endif// LAB7_CONSTANTS_H
