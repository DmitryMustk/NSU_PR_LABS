#include "node.h"

#include <stdlib.h>

static int is_red(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->col == red;
}

static void color_flip(Node *node) {
    node->col = node->col ^ 1;
    node->child[left]->col = node->child[left]->col ^ 1;
    node->child[right]->col = node->child[right]->col ^ 1;
}

static Node *rotate(Node *node, int dir) {
    Node *tmp = node->child[!dir];
    node->child[!dir] = tmp->child[dir];
    tmp->child[dir] = node;
    tmp->col = node->col;
    node->col = red;
    return tmp;
}

static Node *double_rotate(Node *node, int dir) {
    node->child[!dir] = rotate(node->child[!dir], !dir);
    return rotate(node, dir);
}

Node *insert_fix_up(Node *node, int dir) {
    if (is_red(node->child[dir])) {
        if (is_red(node->child[!dir])) {
            if (is_red(node->child[dir]->child[dir]) || is_red(node->child[dir]->child[!dir])) {
                color_flip(node);
            }
        } else {
            if (is_red(node->child[dir]->child[dir])) {
                node = rotate(node, !dir);
            } else if (is_red(node->child[dir]->child[!dir])) {
                node = double_rotate(node, !dir);
            }
        }
    }
    return node;
}
