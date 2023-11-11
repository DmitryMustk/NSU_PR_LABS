#include "prim_info.h"
#include "constants.h"

#include <stdlib.h>

int create_prim_info(prim_info** self, const int ver_num) {
    *self = malloc(sizeof(prim_info));
    if (!*self) {
        return other_error;
    }
    (*self)->min_e = malloc(sizeof(unsigned int) * ver_num);
    if (!(*self)->min_e)
        return other_error;
    (*self)->used = malloc(sizeof(char) * ver_num);
    if (!(*self)->used)
        return other_error;
    (*self)->sel_e = malloc(sizeof(short int) * ver_num);
    if (!(*self)->sel_e)
        return other_error;
    return no_error;
}

void destroy_prim_info(prim_info** self) {
    free((*self)->min_e);
    free((*self)->used);
    free((*self)->sel_e);
    free(*self);
}
