#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cmp {
	int id;
    char *file_path;
	int nt;
	int nx;
	float *data;
};

struct trace {
	int nt;
	float x_offset;
	float y_offset;
	int shot_id;
	int cmp_id;
};
