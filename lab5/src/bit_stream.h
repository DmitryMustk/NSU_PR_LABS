#ifndef LAB5_BIT_STREAM_H
#define LAB5_BIT_STREAM_H

#include "constants.h"

#include <stdio.h>
typedef struct BitStream {
    FILE* file;
    unsigned char data;
    int pos;
}BitStream;
BitStream* create_bit_stream(FILE* file);
error_code read_bit(BitStream* stream, int* bit);
error_code read_byte(BitStream* stream, unsigned char* byte);
void write_bit(int bit, BitStream* stream);
void write_byte(unsigned char byte, BitStream* stream);
void flush(BitStream* stream);
#endif //LAB5_BIT_STREAM_H
