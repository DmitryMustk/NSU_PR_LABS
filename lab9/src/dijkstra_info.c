#include "dijkstra_info.h"
#include "constants.h"

#include <stdlib.h>

int create_dijkstra_info(dijkstra_info** self, const int ver_num) {
    *self = malloc(sizeof(dijkstra_info));
    if(!*self){
        return other_error;
    }
    (*self)->min_d = malloc(sizeof(unsigned int) * ver_num);
    if (!(*self)->min_d)
        return other_error;
    (*self)->used = malloc(sizeof(char) * ver_num);
    if (!(*self)->used)
        return other_error;
    (*self)->parent = malloc(sizeof(short int) * ver_num);
    if (!(*self)->parent)
        return other_error;
    return no_error;
}

void destroy_dijkstra_info(dijkstra_info** self) {
    free((*self)->min_d);
    free((*self)->used);
    free((*self)->parent);
    free(*self);
}
