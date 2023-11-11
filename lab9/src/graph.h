#ifndef LAB9_GRAPH_H
#define LAB9_GRAPH_H
#include "constants.h"
typedef struct graph_t {
    int ver_num;
    int edge_num;
    int start;
    int finish;
    unsigned int* weights;
} graph_t;
error_code fill_graph(graph_t** self, const char* in_stream);
error_code dijkstra(graph_t** self, const char* out_stream);
void print_error(error_code error);
void destroy_graph(graph_t** self);
#endif// LAB9_GRAPH_H
