#ifndef LAB6_0_MEMORY_H
#define LAB6_0_MEMORY_H
typedef struct Memory Memory;
Memory* create_memory(int n);
void* allocate_memory(Memory* memory);
int is_allocate(Memory* memory);
void destroy_memory(Memory* memory);
#endif //LAB6_0_MEMORY_H
