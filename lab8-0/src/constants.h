#ifndef LAB8_0_CONSTANTS_H
#define LAB8_0_CONSTANTS_H
typedef enum error_code {
    no_error = 0,
    other_error,
    bad_number_of_lines,
    bad_number_of_vertices,
    bad_number_of_edges,
    bad_vertex,
    bad_length,
    impossible_to_sort,
    no_spanning_tree,
} error_code;
#define MAX_VERTICES_COUNT 5000
#endif// LAB8_0_CONSTANTS_H
