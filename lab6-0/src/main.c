#include <stdlib.h>

#include "avlTree.h"

int main(void) {
	const char *in_stream = "in.txt", *out_stream = "out.txt";
	AVLTree *tree = NULL;
	if(!fill_tree(&tree, in_stream)) return 0;
    const int height = get_tree_hight(&tree);
	if(!print_tree_height(height, out_stream)) return 0;
	destroy_tree(&tree);
	return 0;
}
