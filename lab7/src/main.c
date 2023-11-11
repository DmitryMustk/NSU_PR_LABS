#include <stdlib.h>

#include "constants.h"
#include "graph.h"

int main(void) {
    const char* in_stream = "in.txt", *out_stream = "out.txt";
    graph_t* graph = NULL;
    error_code error = fill_graph(&graph, in_stream);
    error = tarjan_algorithm(&graph, error);
    if(error != no_error){
        print_error(error, out_stream);
        destroy_graph(&graph);
        return 0;
    }
    print_graph(&graph, out_stream);
    destroy_graph(&graph);
    return 0;
}
