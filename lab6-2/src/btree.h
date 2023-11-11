#ifndef LAB6_2_BTREE_H
#define LAB6_2_BTREE_H
#include "node.h"
typedef struct BTree {
    int order;
    int height;
    Node* root;
} BTree;
void destroy_tree(BTree** self);
int fill_tree(BTree** self, const char* in_file);
int print_height(BTree** self, const char* out_file);
#endif //LAB6_2_BTREE_H
