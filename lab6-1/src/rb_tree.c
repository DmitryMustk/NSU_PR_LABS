#include "rb_tree.h"
#include "node.h"

#include <stdlib.h>

static Node *insert_node(Node *root, Node *tree, int data, int index) {
    if (!root) {
        tree[index].data = data;
        tree[index].col = red;
        tree[index].child[right] = NULL;
        tree[index].child[left] = NULL;
        root = &tree[index];
        return root;
    }
    int dir = data > root->data;
    root->child[dir] = insert_node(root->child[dir], tree, data, index);
    return insert_fix_up(root, dir);
}

static int create_tree(RBTree** self, int number_of_nodes){
    *self = malloc(sizeof(RBTree));
    if(!*self)
        return 0;
    (*self)->tree = malloc(sizeof(Node) * number_of_nodes);
    if(!(*self)->tree){
        return 0;
    }
    (*self)->root = NULL;
    (*self)->number_of_nodes = number_of_nodes;
    return 1;
}

void destroy_tree(RBTree** self){
    free((*self)->tree);
    free(*self);
}

static int black_height(RBTree** self) {
    int ans = 0;
    Node* tmp = (*self)->root;
    while (tmp) {
        if (tmp->col == black) {
            ans++;
        }
        tmp = tmp->child[left];
    }
    return ans;
}

int get_tree_height(RBTree** self) {
    return black_height(self) + 1;
}

int fill_tree(RBTree** self, const char* in_stream){
    FILE *fp = fopen(in_stream, "r");
    if(!fp)
        return 0;
    int number_of_nodes;
    if (!fscanf(fp, "%d", &number_of_nodes)) {
        fclose(fp);
        return 0;
    }
    if(number_of_nodes <= 0){
        printf("0");
        fclose(fp);
        return 0;
    }
    if (!create_tree(self, number_of_nodes)) {
        fclose(fp);
        return 0;
    }
    int tmpValue;
    for (int i = 0; i < number_of_nodes; i++) {
        if (!fscanf(fp, "%d", &tmpValue)) {
            destroy_tree(self);
            fclose(fp);
            return 0;
        }
        (*self)->root = insert_node((*self)->root, (*self)->tree, tmpValue, i);
    }
    (*self)->root->col = black;
    fclose(fp);
    return 1;
}
