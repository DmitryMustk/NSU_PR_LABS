#include "huffman.h"

#include <stdio.h>

int main(void) {
    FILE* in_file = fopen("in.txt", "rb");
    FILE* out_file = fopen("out.txt", "wb");

    char mode = fgetc(in_file);
    if (mode == 'c') {
        encode(in_file, out_file);
    }
    if (mode == 'd') {
        decode(in_file, out_file);
    }

    fclose(in_file);
    fclose(out_file);

    return 0;
}
