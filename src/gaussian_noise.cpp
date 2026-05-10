#include "../include/gaussian_noise.h"

GaussianNoise::GaussianNoise() {} // Constructor

void GaussianNoise::add_noise(const complex_signal *input,
                              complex_signal *output,
                              int length, 
                              double snr_db,
                              int bits_per_symbol)
{
    double total_energy = 0.0;
    for (int i = 0; i < length; ++i) {
        total_energy += std::norm((*input)[i]);
    }

    double Es = total_energy / length;

    double EbNo_linear = pow(10.0, snr_db / 10.0);
    double EsNo_linear = EbNo_linear * bits_per_symbol;
    double N0 = Es / EsNo_linear;

    double sigma = sqrt(N0 / 2.0);
    
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0.0, sigma);

    for (int i = 0; i < length; ++i) {
        complex<double> noise(dist(gen), dist(gen));
        (*output)[i] = (*input)[i] + noise;
    }
}
