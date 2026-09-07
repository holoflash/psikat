#ifndef HELPERS_H
#define HELPERS_H

int    wrap_index(int index, int max);
double samples_to_seconds(double samples, double channels, double sample_rate);
double subdivision_to_seconds(double bpm, double subdivision);
double subdivision_to_samples(double bpm, double subdivision, double sample_rate);

#endif
