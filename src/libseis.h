// Libseis.h

float *gain(const float *data, int nt, int nx, float dt, float pow);
float *read_float(char path[], int nt, int nx);
void write_float(char path[], float *data, int nt, int nx);

typedef enum {
  SINGLE,
  DOUBLE,
} PRECISION;

struct gather {
  int id;
  char *file_path;
  int nt;
  int nx;
  float *data;
  PRECISION precision;
};
