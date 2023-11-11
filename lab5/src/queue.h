#ifndef LAB5_QUEUE_H
#define LAB5_QUEUE_H
#include "tree.h"
typedef struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    struct QueueNode* head;
}Queue;

Queue* create_queue(void);
int is_empty(Queue* queue);
int push(TreeNode* tree_node, Queue* queue);
TreeNode* delete(Queue* queue);
#endif //LAB5_QUEUE_H
