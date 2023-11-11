#ifndef LAB6_1_NODE_H
#define LAB6_1_NODE_H
#include "constants.h"
typedef struct Node {
    int data;
    colour col;
    struct Node *child[2];
} Node;
Node *insert_fix_up(Node *node, int dir);
#endif //LAB6_1_NODE_H
