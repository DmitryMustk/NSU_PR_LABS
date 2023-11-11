#ifndef LAB9_DIJKSTRA_INFO_H
#define LAB9_DIJKSTRA_INFO_H
typedef struct dijkstra_info {
    unsigned int* min_d;
    char* used;
    short int* parent;
} dijkstra_info;
int create_dijkstra_info(dijkstra_info** self, int ver_num);
void destroy_dijkstra_info(dijkstra_info** self);
#endif// LAB9_DIJKSTRA_INFO_H
