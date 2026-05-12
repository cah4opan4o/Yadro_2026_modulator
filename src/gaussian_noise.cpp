#include "../include/gaussian_noise.h"

GaussianNoise::GaussianNoise() {} // Constructor

void GaussianNoise::add_noise(const complex_signal *input,
                              complex_signal *output,
                              int length, 
                              float snr_db,
                              int bits_per_symbol)
{
    float total_energy = 0.0;
    for (int i = 0; i < length; ++i) {
        total_energy += std::norm((*input)[i]);
    }

    float Es = total_energy / length;

    float EbNo_linear = pow(10.0, snr_db / 10.0);
    float EsNo_linear = EbNo_linear * bits_per_symbol;
    float N0 = Es / EsNo_linear;

    float sigma = sqrt(N0 / 2.0);
    
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<float> dist(0.0, sigma);

    for (int i = 0; i < length; ++i) {
        complex<float> noise(dist(gen), dist(gen));
        (*output)[i] = (*input)[i] + noise;
    }
}
