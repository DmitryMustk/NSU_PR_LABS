#include "code.h"
#include "constants.h"

#include <stdlib.h>

void get_codes(TreeNode* root, Code* codes, const unsigned long long code, const int cur_len) {
    if (is_leaf(root)) {
        codes[root->symbol].code = code;
        codes[root->symbol].length = cur_len;
        return;
    }
    get_codes(root->left, codes, code << 1 , cur_len + 1);
    get_codes(root->right, codes, (code << 1) | 1, cur_len + 1);
}

Code* make_code_table(TreeNode* root) {
    Code* codes = malloc(sizeof(struct Code) * ALPHABET_SIZE);
    if(!codes){
        return NULL;
    }
    get_codes(root, codes, 0, 0);
    return codes;
}

void pack(const unsigned char c, Code* codes, BitStream* stream) {
    for (int i = codes[c].length - 1; i >= 0; i--) {
        int bit = (codes[c].code >> i) & 1;
        write_bit(bit, stream);
    }
}
