//
// Created by dmtr on 04.04.23.
//

#ifndef LAB10_POINT_H
#define LAB10_POINT_H
typedef struct point_t {
	int x;
	int y;
} point_t;

point_t* create_point_t(int x, int y);
double get_ccw(point_t* p1, point_t* p2, point_t* p3);
int compare_points(const void* x, const void* y);
void destroy_point_t(point_t* self);

#endif// LAB10_POINT_H
