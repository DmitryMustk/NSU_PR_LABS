#ifndef LAB6_0_NODE_H
#define LAB6_0_NODE_H
struct Memory;
typedef struct node node;
int get_size(void);
unsigned char get_height(const node *n)   ;
node *insert_node(node *n, int v, struct Memory *memory);
#endif// LAB6_0_NODE_H
