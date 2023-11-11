#include "item.h"

#include <stdlib.h>

item_t* create_item_t(const int weight, const int cost) {
    item_t* self = malloc(sizeof(item_t));
    if (!self) return NULL;
    self->weight = weight;
    self->cost = cost;
    return self;
}

void destroy_item(item_t* self) {
    free(self);
}
