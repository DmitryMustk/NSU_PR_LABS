#ifndef LAB5_TREE_H
#define LAB5_TREE_H
#include "constants.h"
#include "bit_stream.h"
typedef struct TreeNode {
    unsigned char symbol;
    int freq;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
int is_leaf(TreeNode* node);
TreeNode* create_tree(int* frequencies);
void pack_tree(TreeNode* root, struct BitStream* stream);
void destroy_tree(TreeNode* root);
TreeNode* unpack_tree(struct BitStream* stream);
error_code unpack(TreeNode* root, BitStream* stream, unsigned char* c);
#endif //LAB5_TREE_H
