#include "bit_stream.h"
#include "code.h"
#include "constants.h"
#include "huffman.h"
#include "tree.h"

#include <stdlib.h>

int* create_frequency_table(FILE* in) {
    int* frequencies = calloc(ALPHABET_SIZE, sizeof(int));
    if(!frequencies){
        return NULL;
    }
    while (!feof(in)) {
        unsigned char curr_symbol = fgetc(in);
        if (feof(in)) {
            break;
        }

        frequencies[curr_symbol] += 1;
    }

    fseek(in, 1, SEEK_SET);
    return frequencies;
}

void encode(FILE* raw, FILE* zipped) {
    if (fgetc(raw) == EOF)
        return;
    else
        fseek(raw, 1, SEEK_SET);

    BitStream* stream = create_bit_stream(zipped);
    int* frequencies = create_frequency_table(raw);
    TreeNode* root = create_tree(frequencies);
    Code* codes = make_code_table(root);
    if(!stream || !frequencies || !root || !codes){
        destroy_tree(root);
        free(codes);
        free(frequencies);
        free(stream);
        return;
    }
    int length = root->freq;
    fwrite(&length, sizeof(int), 1, zipped);

    pack_tree(root, stream);
    while (!feof(raw)) {
        unsigned char c = fgetc(raw);
        if (feof(raw)) {
            break;
        }

        pack(c, codes, stream);
    }
    flush(stream);
    destroy_tree(root);
    free(codes);
    free(frequencies);
    free(stream);
}

void decode(FILE* zipped, FILE* unzipped) {
    if (fgetc(zipped) == EOF)
        return;
    else
        fseek(zipped, 1, SEEK_SET);

    BitStream* stream = create_bit_stream(zipped);
    if(!stream){
        return;
    }

    int length;
    if (fread(&length, sizeof(int), 1, zipped) != 1) {
        return;
    }

    TreeNode* root = unpack_tree(stream);
    if(!root){
        free(stream);
        return;
    }
    for (int i = 0; i < length; i++) {
        unsigned char c;
        if(unpack(root, stream, &c) == read_error){
            destroy_tree(root);
            free(stream);
            return;
        }
        fwrite(&c, sizeof(char), 1, unzipped);
    }

    destroy_tree(root);
    free(stream);
}
