#ifndef LAB6_2_NODE_H
#define LAB6_2_NODE_H
typedef struct Node {
    int key_count;
    int* keys;
    struct Node** children;
}Node;
void destroy_nodes(Node* root);
int is_leaf(const Node* node);
void move_tail(Node* src, int i, const Node* dst, int j);
int find_child(Node* node, int key);
void add_key(Node* leaf, int key);
#endif //LAB6_2_NODE_H
