#ifndef LAB8_1_PRIM_INFO_H
#define LAB8_1_PRIM_INFO_H
typedef struct prim_info {
    unsigned int* min_e;
    char* used;
    short int* sel_e;
} prim_info;
int create_prim_info(prim_info** self, int ver_num);
void destroy_prim_info(prim_info** self);
#endif// LAB8_1_PRIM_INFO_H
