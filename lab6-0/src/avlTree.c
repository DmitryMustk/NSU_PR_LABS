#include "avlTree.h"
#include "memory.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

struct AVLTree {
    node *root;
    Memory *memory;
};

int create_tree(AVLTree **tree, int number_of_nodes) {
    *tree = malloc(sizeof(AVLTree));
    if (!(*tree))
        return 0;
    (*tree)->root = NULL;
    (*tree)->memory = create_memory(number_of_nodes);
    if (!(*tree)->memory || !is_allocate((*tree)->memory)) {
        destroy_tree(tree);
        return 0;
    }
    return 1;
}

int fill_tree(AVLTree **tree, const char *in_stream) {
    FILE *fp = fopen(in_stream, "r");
    if (!fp)
        return 0;
    int number_of_nodes;
    if (!fscanf(fp, "%d", &number_of_nodes)) {
        fclose(fp);
        return 0;
    }
    if (!create_tree(tree, number_of_nodes)) {
        fclose(fp);
        return 0;
    }
    int val;
    for (int i = 0; i < number_of_nodes; ++i) {
        if (!fscanf(fp, "%d", &val)) {
            fclose(fp);
            return 0;
        }
        (*tree)->root = insert_node((*tree)->root, val, (*tree)->memory);
    }
    fclose(fp);
    return 1;
}

int get_tree_hight(AVLTree** tree) {
    return get_height((*tree)->root);
}

int print_tree_height(const int height, const char *out_stream) {
    FILE *fp = fopen(out_stream, "w");
    if (!fprintf(fp, "%d", height)) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}

void destroy_tree(AVLTree **tree) {
    destroy_memory((*tree)->memory);
    free(*tree);
}
