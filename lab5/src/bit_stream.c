#include <stdio.h>
#include <stdlib.h>

#include "bit_stream.h"
#include "constants.h"

BitStream* create_bit_stream(FILE* file) {
    BitStream* stream = malloc(sizeof(struct BitStream));
    if(!stream){
        return NULL;
    }
    stream->file = file;
    stream->data = 0;
    stream->pos = 0;
    return stream;
}

error_code read_bit(BitStream* stream, int* bit) {
    if (stream->pos == 0) {
        if (fread(&stream->data, sizeof(char), 1, stream->file) != 1) {
            return read_error;
        }
        stream->pos = BUFFER_SIZE;
    }

    stream->pos -= 1;
    *bit = (stream->data >> stream->pos) & 1;
    return no_error;
}

void write_bit(const int bit, BitStream* stream) {
    if (stream->pos == BUFFER_SIZE) {
        fwrite(&stream->data, sizeof(char), 1, stream->file);
        stream->data = 0;
        stream->pos = 0;
    }

    stream->data = bit | (stream->data << 1);
    stream->pos += 1;
}

error_code read_byte(BitStream* stream, unsigned char* byte) {
    *byte = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        *byte = *byte << 1;
        int bit;
        if(read_bit(stream, &bit) == read_error)
            return read_error;
        *byte = *byte | bit;
    }

    return no_error;
}

void write_byte(const unsigned char byte, BitStream* stream) {
    for (int i = BUFFER_SIZE - 1; i >= 0; i--) {
        int bit = (byte >> i) & 1;
        write_bit(bit, stream);
    }
}

void flush(BitStream* stream) {
    stream->data = stream->data << (BUFFER_SIZE - stream->pos);
    fwrite(&stream->data, sizeof(char), 1, stream->file);
}
