#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_bin(char *path, int nt, int nx) {

	FILE *fptr;
	int total_read = 0;
	double* data;

	data = (double *)malloc(nt * nx * sizeof(double));

	fptr = fopen(path, "rb");
	if (fptr == NULL) {
		printf("unable to open file at %s\n", path);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nt * nx; i++){
		fread(&data[i], sizeof(double), 1, fptr);
		printf("%.53f\n", data[i]);
	}

	fclose(fptr);
	return 0;
}

int main() {
	char *file_path = "./shot100.bin";
	int nt = 1000;
	int nx = 3101;

	open_bin(file_path, nt, nx);
}
