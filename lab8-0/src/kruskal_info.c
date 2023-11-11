#include "constants.h"
#include "kruskal_info.h"

#include <stdlib.h>

int create_kruskal_info(kruskal_info **self, const int ver_num) {
    *self = malloc(sizeof(kruskal_info));
    if (!*self)
        return other_error;
    (*self)->parent = malloc(sizeof(int) * ver_num);
    if(!(*self)->parent){
        destroy_kruskal_info(self);
        return other_error;
    }
    (*self)->vert = malloc(sizeof(char) * ver_num);
    if(!(*self)->vert){
        destroy_kruskal_info(self);
        return other_error;
    }
    (*self)->rank = malloc(sizeof(int) * ver_num);
    if(!(*self)->rank) {
        destroy_kruskal_info(self);
        return other_error;
    }
    for(int i = 0; i < ver_num; ++i){
        (*self)->vert[i] = 0;
        (*self)->rank[i] = 0;
        (*self)->parent[i] = i;
    }
    return no_error;
}

void destroy_kruskal_info(kruskal_info** self){
    free((*self)->parent);
    free((*self)->vert);
    free((*self)->rank);
    free(*self);
}
