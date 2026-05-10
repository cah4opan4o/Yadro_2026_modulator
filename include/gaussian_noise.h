#ifndef GAUSSIAN_NOISE_H
#define GAUSSIAN_NOISE_H
#include "utils.h"

class GaussianNoise
{
public:
    GaussianNoise(); // Constructor
    void add_noise(const complex_signal *input,
                   complex_signal *output,
                   int length, double snr_db);
};
#endif // GAUSSIAN_NOISE_H