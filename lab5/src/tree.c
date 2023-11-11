#include "bit_stream.h"
#include "constants.h"
#include "queue.h"
#include "tree.h"

#include <stdlib.h>

TreeNode* create_tree_node(const unsigned char symbol, const int freq, TreeNode* left, TreeNode* right) {
    TreeNode* node = malloc(sizeof(TreeNode));
    if(!node){
        return NULL;
    }
    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

int is_leaf(TreeNode* node) {
    return !node->left;
}

void destroy_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

void pack_tree(TreeNode* root, BitStream* stream) {
    if (is_leaf(root)) {
        write_bit(1, stream);
        write_byte(root->symbol, stream);
        return;
    }
    write_bit(0, stream);
    pack_tree(root->left, stream);
    pack_tree(root->right, stream);
}

TreeNode* unpack_tree(BitStream* stream) {
    int bit;
    if(read_bit(stream, &bit) == read_error)
        return NULL;
    if (bit == 1) {
        unsigned char byte;
        if(read_byte(stream, &byte) == read_error)
            return NULL;
        return create_tree_node(byte, 0, NULL, NULL);
    }
    TreeNode* left = unpack_tree(stream);
    TreeNode* right = unpack_tree(stream);
    return create_tree_node(0, 0, left, right);

}

TreeNode* create_tree(int* frequencies) {
    Queue* priority_queue = create_queue();
    if(!priority_queue){
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] != 0) {
            TreeNode* node = create_tree_node(i, frequencies[i], NULL, NULL);
            if(!node){
                free(priority_queue);
                return NULL;
            }
            if(!push(node, priority_queue)){
                free(priority_queue);
                return NULL;
            }
        }
    }

    if (priority_queue->head->next == NULL) {
        TreeNode* root = delete(priority_queue);
        free(priority_queue);
        return root;
    }

    while (1) {
        TreeNode* left = delete(priority_queue);
        TreeNode* right = delete(priority_queue);
        TreeNode* root = create_tree_node(0, left->freq + right->freq, left, right);
        if(!root){
            free(priority_queue);
            return NULL;
        }

        if (is_empty(priority_queue)) {
            free(priority_queue);
            return root;
        }

        if(!push(root, priority_queue)){
            free(priority_queue);
            return NULL;

        }
    }
}

error_code unpack(TreeNode* root, BitStream* stream, unsigned char* c) {
    TreeNode* curr_node = root;
    while (!is_leaf(curr_node)) {
        int bit;
        if(read_bit(stream, &bit) == read_error){
            return read_error;
        }
        if (bit == 0)
            curr_node = curr_node->left;
        else
            curr_node = curr_node->right;
    }

    *c = curr_node->symbol;
    return no_error;
}

