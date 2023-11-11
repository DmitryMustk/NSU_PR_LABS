#include "node.h"

#include <stdlib.h>
#include <string.h>

int is_leaf(const Node* node) {
    return node->children == NULL;
}

void destroy_nodes(Node* root) {
    if (!is_leaf(root)) {
        for (int i = 0; i < root->key_count + 1; i++)
            destroy_nodes(root->children[i]);
        free(root->children);
    }
    free(root->keys);
    free(root);
}

void move_tail(Node* src, const int i, const Node* dst, int j) {
    int n = src->key_count - i;
    memmove(dst->keys + j, src->keys + i, n * sizeof(int));
    if (!is_leaf(src))
        memmove(dst->children + j, src->children + i, (n + 1) * sizeof(struct Node*));
}

int find_child(Node* node, const int key) {
    int low = 0;
    int high = node->key_count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (node->keys[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return high + 1;
}

void add_key(Node* leaf, const int key) {
    int i = find_child(leaf, key);
    move_tail(leaf, i, leaf, i + 1);
    leaf->keys[i] = key;
    leaf->key_count++;
}
