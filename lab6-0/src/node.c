#include "node.h"
#include "memory.h"

struct node {
	int val;
	unsigned char height;
	struct node *left;
	struct node *right;
};

int get_size(void) {
	return sizeof(node);
}

static node *create_node(const int value, Memory *memory) {
	node *node = allocate_memory(memory);
	node->val = value;
	node->left = node->right = 0;
	node->height = 1;
	return node;
}

unsigned char get_height(const node *n) {
	return n ? n->height : 0;
}

static int get_bfactor(const node *p) {
	return get_height(p->right) - get_height(p->left);
}

static void fix_height(node *p) {
	unsigned char nl = get_height(p->left);
	unsigned char nr = get_height(p->right);
	p->height = (nl > nr ? nl : nr) + (unsigned char)1;
}

static node *rotate_right(node *n) {
	node *q = n->left;
	n->left = q->right;
	q->right = n;
	fix_height(n);
	fix_height(q);
	return q;
}

static node *rotate_left(node *n) {
	node *p = n->right;
	n->right = p->left;
	p->left = n;
	fix_height(n);
	fix_height(p);
	return p;
}

static node *balance(node *n) {
	fix_height(n);
	if(get_bfactor(n) == 2) {
		if(get_bfactor(n->right) < 0) n->right = rotate_right(n->right);
		return rotate_left(n);
	}
	if(get_bfactor(n) == -2) {
		if(get_bfactor(n->left) > 0) n->left = rotate_left(n->left);
		return rotate_right(n);
	}
	return n;
}

node *insert_node(node *n, int val, Memory *memory) {
	if(!n) return create_node(val, memory);
	if(val < n->val)
		n->left = insert_node(n->left, val, memory);
	else
		n->right = insert_node(n->right, val, memory);
	return balance(n);
}
