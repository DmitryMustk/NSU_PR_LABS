#include "btree.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

static Node* create_node(BTree** self, const int is_leaf) {
    Node* new_node = malloc(sizeof(struct Node));
    new_node->key_count = 0;
    new_node->keys = malloc((2 * (*self)->order - 1) * sizeof(int));
    if (is_leaf) {
        new_node->children = NULL;
        return new_node;
    }
    new_node->children = malloc((2 * (*self)->order) * sizeof(struct BTreeNode*));
    return new_node;
}

static int create_tree(BTree** self, const int order) {
    *self = malloc(sizeof(BTree));
    if(!(*self))
        return 0;
    (*self)->order = order;
    (*self)->height = 0;
    (*self)->root = NULL;
    return 1;
}

void destroy_tree(BTree** self) {
    if ((*self)->root != NULL)
        destroy_nodes((*self)->root);
    free((*self));
}

static int is_full(BTree** self, Node* node) {
    return node->key_count == 2 * (*self)->order - 1;
}

static void split(BTree** self, Node* node, const int child) {
    Node* old_node = node->children[child];
    Node* new_node = create_node(self, is_leaf(old_node));
    move_tail(old_node, (*self)->order, new_node, 0);
    old_node->key_count = (*self)->order - 1;
    new_node->key_count = (*self)->order - 1;
    move_tail(node, child, node, child + 1);
    node->keys[child] = old_node->keys[(*self)->order - 1];
    node->children[child + 1] = new_node;
    node->key_count++;
}

static void insert_non_full(BTree** self, Node* node, const int key) {
    if (!is_leaf(node)) {
        int child = find_child(node, key);
        if (is_full(self, node->children[child])) {
            split(self, node, child);
            child = key < node->keys[child] ? child : child + 1;
        }
        insert_non_full(self, node->children[child], key);
        return;
    }
    add_key(node, key);
}

static void insert(BTree** self, const int key) {
    if ((*self)->root == NULL) {
        (*self)->root = create_node(self, 1);
        (*self)->height++;
    }
    if (is_full(self, (*self)->root)) {
        Node *new_root = create_node(self, 0);
        new_root->children[0] = (*self)->root;
        split(self, new_root, 0);
        (*self)->root = new_root;
        (*self)->height++;
    }
    insert_non_full(self, (*self)->root, key);
}

int fill_tree(BTree** self, const char* in_file) {
    FILE* fp = fopen(in_file, "r");
    int order, number_of_keys;
    if (fscanf(fp, "%d %d", &order, &number_of_keys) != 2) {
        fclose(fp);
        return 0;
    }
    if(!create_tree(self, order)){
        fclose(fp);
        return 0;
    }
    for (int i = 0; i < number_of_keys; i++) {
        int key;
        if (fscanf(fp, "%d", &key) != 1) {
            destroy_tree(self);
            fclose(fp);
            return 0;
        }
        insert(self, key);
    }
    fclose(fp);
    return 1;
}

int get_height(BTree** self){
    return (*self)->height;
}

int print_height(BTree** self, const char* out_file){
    FILE* fp = fopen(out_file, "w");
    if(!fp){
        return 0;
    }
    fprintf(fp, "%d", get_height(self));
    fclose(fp);
    return 1;
}
