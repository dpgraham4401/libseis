// Libseis.h
// Libseis is a small, simple, collections of functions for seismic processing.
// David Graham - 2023-15-01

typedef enum {
  SINGLE,
  DOUBLE,
} PRECISION;

struct Gather {
  int id;
  int nt;
  int nx;
  float dt;
  float *data;
  PRECISION precision;
};

float *gain(const float *data, int nt, int nx, float dt, float pow);
float *read_float(char path[], int nt, int nx);
void write_float(char path[], float *data, int nt, int nx);

/*
 * Function:  gain_cmp
 * --------------------
 * Applies a time-variant scaling to a series of seismic traces in the same gather.
 *    It can be used to compensate for exponential decay in amplitude with time
 *    for a monochromatic source signal.
 *    See "Tpow: an estimator of seismic amplitude decay" by Fowler & Claerbout
 *    nt' = nt * (dt * t^pow)
 *
 * Inputs:
 *    *gather: A pointer to a shot, CMP, or other seismic gather with all necessary fields.
 *    pow: The power (float) applied to the seismic trace as a function of time.
 *
 *  returns: A pointer to a new gather with the supplied Tpow applied.
 *      All gather attributes, besides the seismic data, are copied from the original gather
 *
 */
int gain_cmp(struct Gather *gather, float pow);
