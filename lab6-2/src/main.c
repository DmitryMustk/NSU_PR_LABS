#include "btree.h"

#include <stdlib.h>

int main(void) {
    const char* in_file = "in.txt", *out_file = "out.txt";
    BTree* tree = NULL;
    if(!fill_tree(&tree, in_file)){
        destroy_tree(&tree);
        return 0;
    }
    if(!print_height(&tree, out_file)){
        destroy_tree(&tree);
        return 0;
    }
    destroy_tree(&tree);
    return 0;
}
