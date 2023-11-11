#ifndef LAB7_GRAPH_H
#define LAB7_GRAPH_H
typedef struct graph_t {
    int verticle_number;
    int edge_number;
    short* sorted;
    char* matrix;
} graph_t;
int fill_graph(graph_t** self, const char* in_stream);
int tarjan_algorithm(graph_t** self, error_code error);
void destroy_graph(graph_t** self);
void print_graph(graph_t** self, const char* out_stream);
void print_error(error_code error, const char* out_stream);
#endif// LAB7_GRAPH_H
