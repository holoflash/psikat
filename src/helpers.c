#include "helpers.h"

inline int wrap_index(int index, int max) { return ((index % max) + max) % max; }

inline double samples_to_seconds(double samples, double channels, double sample_rate) {
    return samples / (channels * sample_rate);
}

inline double subdivision_to_seconds(double bpm, double subdivision) { return (60.0 / bpm) * (4.0 / subdivision); }

inline double subdivision_to_samples(double bpm, double subdivision, double sample_rate) {
    return (60.0 / bpm) * (4.0 / subdivision) * sample_rate;
}

Vec2 get_coords_to_center(Vec2 target, Vec2 object) {
    return (Vec2){.x = (target.x / 2) - (object.x / 2), .y = (target.y / 2) + (object.y / 2)};
}
