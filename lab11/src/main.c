#include <stdlib.h>

#include "knapsack.h"

int main(void) {
    const char* in_stream = "in.txt", *out_stream = "out.txt";
    knapsack_t* knapsack = NULL;
    fill_knapsack(&knapsack, in_stream);
    print_result(&knapsack, out_stream);
    return 0;
}
