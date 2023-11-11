#ifndef LAB6_1_RB_TREE_H
#define LAB6_1_RB_TREE_H
#include "node.h"
#include "stdio.h"
typedef struct RBTree {
    Node* tree;
    Node* root;
    int number_of_nodes;
} RBTree;
int get_tree_height(RBTree** self);
int fill_tree(RBTree** self, const char* in_stream);
void destroy_tree(RBTree** self);
#endif //LAB6_1_RB_TREE_H
