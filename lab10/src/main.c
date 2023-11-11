#include <stdio.h>

#include "convex_hull.h"

int main(void) {
	const char *in_stream = "in.txt", *out_stream = "out.txt";
	convex_hull* convexHull = NULL;
	if(!fill_convex_hull(&convexHull, in_stream)) return 0;
	get_convex_hull(&convexHull, out_stream);
	return 0;
}
