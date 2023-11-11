#include "knapsack.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>

static void destroy_knapsack(knapsack_t** self);
static int knapsack_algorithm(knapsack_t** self, int length, int height);
static int max(int x, int y);
static int get_max_cost(knapsack_t** self);

static int create_knapsack(knapsack_t** self, const int max_items, const int max_weight) {
    *self = malloc(sizeof(knapsack_t));
    if (!*self)
        return 0;
    (*self)->max_items = max_items;
    (*self)->max_weight = max_weight;
    (*self)->table = malloc(sizeof(int*) * (max_weight + 1));
    if (!(*self)->table) {
        destroy_knapsack(self);
        return 0;
    }
    for (int i = 0; i <= max_weight; ++i) {
        (*self)->table[i] = malloc(sizeof(int) * (max_items + 1));
        if (!(*self)->table[i]) {
            destroy_knapsack(self);
            return 0;
        }
    }
    (*self)->objects = malloc(sizeof(item_t*) * (*self)->max_items);
    if (!(*self)->objects) {
        destroy_knapsack(self);
        return 0;
    }
    (*self)->order = malloc(sizeof(item_t*) * (*self)->max_items);
    if (!(*self)->order) {
        destroy_knapsack(self);
        return 0;
    }
    return 1;
}

static int max(const int x, const int y) {
    return x <= y ? y : x;
}

static int get_max_cost(knapsack_t** self) {
    for (int i = 0; i < (*self)->max_weight + 1; ++i) {
        (*self)->table[i][0] = 0;
    }
    for (int i = 0; i < (*self)->max_items + 1; ++i) {
        (*self)->table[0][i] = 0;
    }
    for (int i = 1; i < (*self)->max_items + 1; ++i) {
        for (int j = 1; j < (*self)->max_weight + 1; ++j) {
            if (j >= (*self)->objects[i - 1]->weight)
                (*self)->table[j][i] = max((*self)->table[j][i - 1],
                                           (*self)->objects[i - 1]->cost + (*self)->table[j - (*self)->objects[i - 1]->weight][i - 1]);
            else
                (*self)->table[j][i] = (*self)->table[j][i - 1];
        }
    }
    return (*self)->table[(*self)->max_weight][(*self)->max_items];
}

int fill_knapsack(knapsack_t** self, const char* in_stream) {
    FILE* fp = fopen(in_stream, "r");
    int max_items, max_weight;
    if (fscanf(fp, "%d %d", &max_items, &max_weight) != 2) {
        fclose(fp);
        return 0;
    }
    if (!create_knapsack(self, max_items, max_weight)) {
        fclose(fp);
        return 0;
    }
    for (int i = 0; i < max_items; ++i) {
        int weight, cost;
        if (fscanf(fp, "%d %d", &weight, &cost) != 2) {
            destroy_knapsack(self);
            fclose(fp);
            return 0;
        }
        (*self)->objects[i] = create_item_t(weight, cost);
    }
    for (int i = 0; i < (*self)->max_items; ++i) {
        (*self)->order[i] = create_item_t(0, 0);
    }
    fclose(fp);
    return 1;
}

static int knapsack_algorithm(knapsack_t** self, const int length, const int height) {
    if (length > 0 && height > 0) {
        if ((*self)->table[length][height] != (*self)->table[length][height - 1]) {
            (*self)->order[height - 1]->weight = (*self)->objects[height - 1]->weight;
            (*self)->order[height - 1]->cost = (*self)->objects[height - 1]->cost;
            return knapsack_algorithm(self, length - (*self)->objects[height - 1]->weight, height - 1);
        }
        else {
            return knapsack_algorithm(self, length, height - 1);
        }
    }
    else {
        return 0;
    }
}

int print_result(knapsack_t** self, const char* out_stream){
    FILE* fp = fopen(out_stream, "w");
    if(!fp) {
        destroy_knapsack(self);
        return 0;
    }
    fprintf(fp, "%d\n", get_max_cost(self));
    knapsack_algorithm(self, (*self)->max_weight, (*self)->max_items);
    for (int i = 0; i < (*self)->max_items; ++i) {
        if ((*self)->order[i]->weight != 0 && (*self)->order[i]->cost != 0) {
            fprintf(fp,"%d %d\n", (*self)->order[i]->weight, (*self)->order[i]->cost);
        }
    }
    destroy_knapsack(self);
    fclose(fp);
    return 1;
}

static void destroy_knapsack(knapsack_t** self) {
    for (int i = 0; i <= (*self)->max_weight; ++i) {
        free((*self)->table[i]);
    }
    free((*self)->table);
    for (int i = 0; i < (*self)->max_items; ++i) {
        destroy_item((*self)->objects[i]);
    }
    for (int i = 0; i < (*self)->max_items; ++i) {
        destroy_item((*self)->order[i]);
    }
    free((*self)->objects);
    free((*self)->order);
    free(*self);
}
