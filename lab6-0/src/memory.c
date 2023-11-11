#include "memory.h"
#include "node.h"

#include <stdlib.h>

struct Memory {
    int allocated_nodes;
    void* space;
};

Memory* create_memory(int n) {
    Memory* memory = malloc(sizeof(Memory));
    if(!memory){
        return NULL;
    }
    memory->allocated_nodes = 0;
    memory->space = malloc(n * get_size());
    return memory;
}

int is_allocate(Memory* memory) {
    return memory->space != NULL;
}

void* allocate_memory(Memory* memory) {
    return (char*) memory->space + (memory->allocated_nodes++) * get_size();
}

void destroy_memory(Memory* memory) {
    free(memory->space);
    free(memory);
}
