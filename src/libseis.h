// Libseis.h
// Libseis is a small, simple, collections of functions for seismic processing.
// David Graham - 2023-15-01

typedef enum {
  SINGLE,
  DOUBLE,
} PRECISION;

/**
 * @brief A collection of seismic traces and attributes
 *
 * @details A gather holds encapsulates all the information about seismic
 * gathers, including the number of traces, the time sampling, number of time
 * samples, and the data itself. It's intended to be generic enough to be used
 * by various seismic gather types, such as CMP, or shot.
 *
 * @param
 * id: (int) The gather's unique identifier
 * @param
 * nt: (int) number times samples in each trace, assumed homogeneous number of
 * samples in each trace
 * @param
 * nx: (int) number traces
 * @param
 * dt: (double) the time sampling of the traces, assumed homogeneous
 * @param
 * data: (pointer) pointer to the array of samples
 * @param
 * precision: (enum PRECISION) the precision of the samples (e.g., double,
 * double)
 */
typedef struct Gather {
  int id;
  int nt;
  int nx;
  double dt;
  double *data;
  PRECISION precision;
} Gather;

double *read_double(char path[], int nt, int nx);

void write_double(char path[], double *data, int nt, int nx);

/**
 * gain_gather
 *
 * @details
 * Applies a time-variant scaling to a series of seismic traces in the same
 * gather. It can be used to compensate for exponential decay (constant Q) in
 * amplitude with time See "Tpow: an estimator of seismic amplitude decay" by
 * Fowler & Claerbout nt' = nt * (dt * t^pow)
 *
 * @param
 * gather: A pointer to a shot, CMP, or other seismic gather with all necessary
 * fields.
 * @param
 * power: The power (double) applied to the seismic trace as a function of time.
 *
 * @returns
 * A pointer to a new gather with the supplied Tpow applied.
 * All gather attributes, besides the seismic data, are copied from the original
 * gather
 *
 */
Gather *gain_gather(Gather *gather, double power);

void display_gather(Gather *gather);
