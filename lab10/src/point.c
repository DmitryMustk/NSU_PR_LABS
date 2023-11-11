#include "point.h"

#include <stdlib.h>

double get_ccw(point_t* p1, point_t* p2, point_t* p3) {
	return ((double)p2->x - p1->x) * ((double)p3->y - p1->y) - ((double)p2->y - p1->y) * ((double)p3->x - p1->x);
}

int compare_points(const void* x, const void* y) {
	const point_t* a = *(const point_t**)x;
	const point_t* b = *(const point_t**)y;
	return !(a->x < b->x || (a->x == b->x && a->y < b->y));
}

point_t* create_point_t(const int x, const int y) {
	point_t* self = malloc(sizeof(point_t));
	if(!self){
		return NULL;
	}
	self->x = x;
	self->y = y;
	return self;
}

void destroy_point_t(point_t* self) {
	free(self);
}
