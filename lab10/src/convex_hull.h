#include "point.h"

#ifndef LAB10_CONVEX_HULL_H
#  define LAB10_CONVEX_HULL_H
typedef struct convex_hull {
	point_t** points;
	int hull_size;
} convex_hull;

int fill_convex_hull(convex_hull** self, const char* in_stream);
int print_convex_hull(convex_hull** self, const char* out_stream);
void get_convex_hull(convex_hull** self, const char* out_stream);
void destroy_convex_hull(convex_hull** self);
void destroy_out_hull(convex_hull* self);
#endif// LAB10_CONVEX_HULL_H
