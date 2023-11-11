#ifndef LAB5_CODE_H
#define LAB5_CODE_H
#include "bit_stream.h"
#include "tree.h"

typedef struct Code {
    unsigned long long code;
    unsigned int length;
} Code;
Code* make_code_table(TreeNode* root);
void pack(unsigned char c, Code* codes, BitStream* stream);
#endif //LAB5_CODE_H
