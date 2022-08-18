#include "libseis.h"
#include "global.h"

/* This function will not be exported and is not
 * directly callable by users of this library.
 */
int add_internal(int x, int y) {
    return x + y;
}

int add(int x, int y) {
    return add_internal(x, y);
}

float *read_float(char *path, int nt, int nx) {
	FILE *fptr;
	float *data;
	data = (float *)malloc(nt * nx * sizeof(float));
	fptr = fopen(path, "rb");
	if (fptr == NULL) {
		printf("unable to open file at %s\n", path);
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < nt * nx; i++){
		fread(&data[i], sizeof(float), 1, fptr);
		// printf("%.53f\n", data[i]);
	}
	fclose(fptr);
	return data;
}

void write_float(char *path, float *data, int nt, int nx) {
	FILE *fptr;
	fptr = fopen(path, "wb");
	if (fptr == NULL) {
		printf("unable to open file at %s\n", path);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < nx * nt; i++) {
		fwrite(&data[i], sizeof(float), 1, fptr);
	}
	fclose(fptr);
	return;
}

float gain(float *data, int nt, int nx, float dt, float pow) {
	for (int n = 0; n < nx; n++) {
		for (int t = 0; t < nt; t++) {
			data[n * t] = data[n * t] * (dt * t * pow); 
		}
	}
	return *data;
}

