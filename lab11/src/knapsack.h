#ifndef LAB11_knapsack_H
#define LAB11_knapsack_H
#include "item.h"

typedef struct knapsack_t {
    int max_weight;
    int max_items;
    int** table;
    item_t** objects;
    item_t** order;
} knapsack_t;

int fill_knapsack(knapsack_t** self, const char* in_stream);
int print_result(knapsack_t** self, const char* out_stream);
#endif// LAB11_knapsack_H
