#ifndef LAB8_0_KRUSKAL_INFO_H
#define LAB8_0_KRUSKAL_INFO_H
typedef struct kruskal_info{
    int* parent;
    char* vert;
    int* rank;
}kruskal_info;
int create_kruskal_info(kruskal_info **self, int ver_num);
void destroy_kruskal_info(kruskal_info** self);
#endif //LAB8_0_KRUSKAL_INFO_H
