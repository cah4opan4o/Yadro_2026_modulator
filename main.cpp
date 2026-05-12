// headers
#include "include/utils.h" // библиотеки и константы
#include "include/modulator.h"
#include "include/demodulator.h"
#include "include/gaussian_noise.h"

using namespace std;

vector<int> generate_bit_stream(int length)
{
    vector<int> bits(length);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);

    for (int i = 0; i < length; ++i)
    {
        bits[i] = dist(gen);
    }
    return bits;
}

int main()
{
    int iterations = 1000;
    int bits_count = 30000; // Кратно 2, 4 и 6

    vector<float> snr_values;
    for (float snr = 1; snr < 20; snr++)
    {
        snr_values.push_back(snr);
    }

    ofstream file("results.csv");
    file << "Modulation/SNR";
    for (float snr : snr_values)
    {
        file << "," << snr;
    }
    file << endl;

    for (int i = 0; i < 3; i++)
    {
        modulation_type mod_type = static_cast<modulation_type>(i);
        Modulator modulator(mod_type);
        Demodulator demodulator(mod_type);
        GaussianNoise noise;

        // Определяем имя модуляции для записи в начало строки
        string mod_name = (i == 0) ? "QPSK" : (i == 1) ? "QAM16"
                                                       : "QAM64";
        file << mod_name;

        for (float snr : snr_values)
        {
            float total_ber = 0.0;
            #pragma omp parallel for reduction(+ : total_ber)
            for (int j = 0; j < iterations; j++)
            {
                vector<int> input_bits = generate_bit_stream(bits_count);

                complex_signal modulated = modulator.modulate(input_bits);

                complex_signal noisy(modulated.size());
                noise.add_noise(&modulated, &noisy, modulated.size(), snr, modulator.bits_per_symbol);

                vector<int> decoded_bits = demodulator.demodulate(&noisy);

                int errors = 0;
                for (size_t k = 0; k < input_bits.size(); ++k)
                {
                    if (input_bits[k] != decoded_bits[k])
                        errors++;
                }
                total_ber += (float)errors / input_bits.size();
            }

            float avg_ber = total_ber / iterations;
            file << "," << avg_ber;

            cout << mod_name << " | SNR: " << snr << " | BER: " << avg_ber << endl;
        }
        file << endl;
    }

    file.close();
    return 0;
}