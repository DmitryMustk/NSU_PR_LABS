#include "rb_tree.h"

#include <stdio.h>
#include <stdlib.h>

int main(void ) {
    const char *in_stream = "in.txt";
    RBTree* rb_tree = NULL;
    if(!fill_tree(&rb_tree, in_stream))
        return 0;
    printf("%d", get_tree_height(&rb_tree));
    destroy_tree(&rb_tree);
    return 0;
}
