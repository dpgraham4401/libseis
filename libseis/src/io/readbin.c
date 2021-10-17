#include "../util/global.h"


double *open_bin(char *path, int nt, int nx) {

	FILE *fptr;
	int total_read = 0;
	double *data;

	data = (double *)malloc(nt * nx * sizeof(double));
	fptr = fopen(path, "rb");

	if (fptr == NULL) {
		printf("unable to open file at %s\n", path);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nt * nx; i++){
		fread(&data[i], sizeof(double), 1, fptr);
		// printf("%.53f\n", data[i]);
	}

	fclose(fptr);
	return data;
}


int main() {
	struct cmp cmp1;
    cmp1.nx = 3101;
    cmp1.nt = 1000;
    cmp1.file_path = "./shot100.bin";

	cmp1.data = open_bin(cmp1.file_path, cmp1.nt, cmp1.nx);
	for(int i = 0; i < cmp1.nt; i++){
		printf("%.53f\n", cmp1.data[i]);
	}
}
