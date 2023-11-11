#include "convex_hull.h"
#include "point.h"

#include <stdio.h>
#include <stdlib.h>

static int create_convex_hull(convex_hull** self, const int number_of_points) {
	*self = malloc(sizeof(convex_hull));
	if(!(*self)) return 0;
	(*self)->hull_size = number_of_points;
	(*self)->points = malloc(sizeof(point_t*) * number_of_points);
	if(!((*self)->points)) {
		destroy_convex_hull(self);
		return 0;
	}
	return 1;
}

int fill_convex_hull(convex_hull** self, const char* in_stream) {
	int number_of_points;
	FILE* fp = fopen(in_stream, "r");
	if(!fp) return 0;
	if(!fscanf(fp, "%d", &number_of_points)) {
		fclose(fp);
		return 0;
	}
	if(number_of_points < 0 || number_of_points > 100000) {
		printf("bad number of points");
		fclose(fp);
		return 0;
	}
	if(!create_convex_hull(self, number_of_points)) {
		fclose(fp);
		return 0;
	}
	for(int i = 0; i < number_of_points; ++i) {
		int x, y;
		if(fscanf(fp, "%d %d", &x, &y) != 2) {
			printf("bad number of lines");
			(*self)->hull_size = i;
			destroy_convex_hull(self);
			fclose(fp);
			return 0;
		}
		point_t* point = create_point_t(x, y);
		if(!point) {
			destroy_convex_hull(self);
			fclose(fp);
			return 0;
		}
		(*self)->points[i] = point;
	}
	fclose(fp);
	return 1;
}

int print_convex_hull(convex_hull** self, const char* out_stream) {
	FILE* fp = fopen(out_stream, "w");
	if(!fp) return 0;
	for(int i = 0; i < (*self)->hull_size; ++i) {
		printf("%d %d\n", (*self)->points[i]->x, (*self)->points[i]->y);
	}
	fclose(fp);
	return 1;
}

void get_convex_hull(convex_hull** self, const char* out_stream) {
	if((*self)->hull_size == 1) {
		print_convex_hull(self, out_stream);
		destroy_convex_hull(self);
		return;
	}
	qsort((*self)->points, (*self)->hull_size, sizeof(point_t*), compare_points);
	convex_hull* out_hull = NULL;
	create_convex_hull(&out_hull, (*self)->hull_size + 1);

	int k = 0;
	for(int i = 0; i < (*self)->hull_size; ++i) {
		while(k >= 2 && get_ccw(out_hull->points[k - 2], out_hull->points[k - 1], (*self)->points[i]) <= 0)
			--k;
		out_hull->points[k++] = (*self)->points[i];
	}

	for(int i = (*self)->hull_size - 2, t = k + 1; i >= 0; --i) {
		while(k >= t && get_ccw(out_hull->points[k - 2], out_hull->points[k - 1], (*self)->points[i]) <= 0)
			--k;
		out_hull->points[k++] = (*self)->points[i];
	}
	out_hull->hull_size = k - 1;
	print_convex_hull(&out_hull, out_stream);
	destroy_convex_hull(self);
	destroy_out_hull(out_hull);
}

void destroy_out_hull(convex_hull* self){
	free(self->points);
	free(self);
}

void destroy_convex_hull(convex_hull** self) {
	for(int i = 0; i < (*self)->hull_size; ++i) {
		destroy_point_t((*self)->points[i]);
	}
	free((*self)->points);
	free(*self);
}
