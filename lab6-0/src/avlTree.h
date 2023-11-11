#ifndef LAB6_0_AVLTREE_H
#define LAB6_0_AVLTREE_H
typedef struct AVLTree AVLTree;
int create_tree(AVLTree **tree, int number_of_nodes);
int fill_tree(AVLTree **tree, const char *in_stream);
int get_tree_hight(AVLTree** tree);
int print_tree_height(int height, const char *out_stream);
void destroy_tree(AVLTree **tree);
#endif //LAB6_0_AVLTREE_H
