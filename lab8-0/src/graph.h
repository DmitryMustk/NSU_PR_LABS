#ifndef LAB8_0_GRAPH_H
#define LAB8_0_GRAPH_H
#include "constants.h"
typedef struct graph_t {
    int ver_num;
    int edge_num;
    int* graph;
} graph_t;
int fill_graph(graph_t** self, const char* in_stream);
int kruskal(graph_t** self);
int print_spanning_tree(graph_t** self, error_code error, const char* out_stream);
int print_error(error_code error, const char* out_stream);
void destroy_graph(graph_t** self);
#endif// LAB8_0_GRAPH_H
