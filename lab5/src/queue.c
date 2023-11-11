#include <stdlib.h>
#include "queue.h"

Queue* create_queue(void) {
    Queue* queue = malloc(sizeof(Queue));
    if(!queue)
        return NULL;
    queue->head = NULL;
    return queue;
}

QueueNode* create_queue_node(TreeNode* tree_node) {
    QueueNode* queue_node = malloc(sizeof(struct QueueNode));
    if(!queue_node){
        return NULL;
    }
    queue_node->node = tree_node;
    queue_node->next = NULL;
    return queue_node;
}

int is_empty(Queue* queue) {
    return queue->head == NULL;
}

int push(TreeNode* tree_node, Queue* queue) {
    QueueNode* new_node = create_queue_node(tree_node);
    if(!new_node){
        return 0;
    }
    if (is_empty(queue) || tree_node->freq < queue->head->node->freq) {
        new_node->next = queue->head;
        queue->head = new_node;
        return 1;
    }

    QueueNode* curr_node = queue->head;
    while (curr_node->next != NULL) {
        if (tree_node->freq < curr_node->next->node->freq) {
            break;
        }

        curr_node = curr_node->next;
    }

    new_node->next = curr_node->next;
    curr_node->next = new_node;
    return 1;
}

TreeNode* delete(Queue* queue) {
    QueueNode* temp = queue->head;
    queue->head = queue->head->next;
    TreeNode* tree_node = temp->node;
    free(temp);
    return tree_node;
}
