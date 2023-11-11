#ifndef LAB9_CONSTANTS_H
#define LAB9_CONSTANTS_H
#define MAX_VERTICES_COUNT 5000
typedef enum error_code {
    no_error = 0,
    other_error,
    bad_number_of_lines,
    bad_number_of_vertices,
    bad_number_of_edges,
    bad_vertex,
    bad_length,
    impossible_to_sort,
} error_code;
#endif// LAB9_CONSTANTS_H
