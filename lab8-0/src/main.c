#include "graph.h"

#include <stdlib.h>

int main(void) {
    graph_t *graph = NULL;
    const char *in_stream = "in.txt", *out_stream = "out.txt";
    error_code error = fill_graph(&graph, in_stream);
    if (error != no_error) {
        print_error(error, out_stream);
        destroy_graph(&graph);
        return 0;
    }
    error = kruskal(&graph);
    print_spanning_tree(&graph, error, out_stream);
    destroy_graph(&graph);
}
