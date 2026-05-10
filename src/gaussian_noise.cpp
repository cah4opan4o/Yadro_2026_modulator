#include "../include/gaussian_noise.h"

GaussianNoise::GaussianNoise() {} // Constructor

void GaussianNoise::add_noise(const complex_signal *input,
                              complex_signal *output,
                              int length, double snr_db)
{
    double total_energy = 0.0;

    for (int i = 0; i < length; ++i)
    {
        std::complex<double> val = (*input)[i];

        double power_of_sample = std::norm(val);

        total_energy += power_of_sample;
    }

    double signal_power = total_energy / length;

    double snr_linear = pow(10.0, snr_db / 10.0);
    double noise_power = signal_power / snr_linear;

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0.0, sqrt(noise_power));

    for (int i = 0; i < length; ++i)
    {
        (*output)[i] = (*input)[i] + dist(gen);
    }
}