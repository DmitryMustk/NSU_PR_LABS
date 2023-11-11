#ifndef LAB8_1_GRAPH_H
#define LAB8_1_GRAPH_H
#include "constants.h"
typedef struct graph_t {
    int ver_num;
    int edge_num;
    unsigned int* weights;
} graph_t;
int fill_graph(graph_t** self, const char* in_stream);
int prim(graph_t** self, const char* out_stream);
int print_error(error_code error, const char* out_stream);
void destroy_graph(graph_t** self);
#endif// LAB8_1_GRAPH_H
