#ifndef LAB11_ITEM_H
#define LAB11_ITEM_H
typedef struct item_t {
    int weight;
    int cost;
} item_t;
item_t* create_item_t(const int weight, const int cost);
void destroy_item(item_t* self);
#endif// LAB11_ITEM_H
