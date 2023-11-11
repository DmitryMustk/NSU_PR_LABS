#include "constants.h"
#include "graph.h"

#include <stdlib.h>

int main(void) {
    graph_t* graph = NULL;
    const char *in_stream = "in.txt", *out_stream = "out.txt";
    error_code error = fill_graph(&graph, in_stream);
    if (error != no_error) {
        print_error(error);
        destroy_graph(&graph);
        return 0;
    }
    dijkstra(&graph, out_stream);
    destroy_graph(&graph);
    return 0;
}
