#include "../include/demodulator.h"

int bits_per_symbol;
Demodulator::Demodulator(modulation_type mod_type)
{
    switch (mod_type)
    {
    case QPSK:
        bits_per_symbol = 2;
        break;
    case QAM16:
        bits_per_symbol = 4;
        break;
    case QAM64:
        bits_per_symbol = 6;
        break;
    default:
        throw invalid_argument("Unsupported modulation type");
    }
}

vector<int> Demodulator::demodulate(const complex_signal *input)
{
    vector<int> output(input->size() * bits_per_symbol);
    switch (bits_per_symbol)
    {
    case 2:
        demodulate_qpsk(input, &output, QPSK_constellation);
        break;
    case 4:
        demodulate_qam16(input, &output, QAM16_constellation);
        break;
    case 6:
        demodulate_qam64(input, &output, QAM64_constellation);
        break;
    default:
        throw invalid_argument("Unsupported modulation type");
    }
    return output;
}

void Demodulator::demodulate_qpsk(const complex_signal *input,
                                  vector<int> *output,
                                  const complex_signal &constellation)
{
    find_nearest_and_decode(input, output, constellation, bits_per_symbol);
}

void Demodulator::demodulate_qam16(const complex_signal *input,
                                   vector<int> *output,
                                   const complex_signal &constellation)
{
    find_nearest_and_decode(input, output, constellation, bits_per_symbol);
}

void Demodulator::demodulate_qam64(const complex_signal *input,
                                   vector<int> *output,
                                   const complex_signal &constellation)
{
    find_nearest_and_decode(input, output, constellation, bits_per_symbol);
}

// Универсальная функция для поиска ближайшей точки
void Demodulator::find_nearest_and_decode(const complex_signal *input,
                                          vector<int> *output,
                                          const complex_signal &constellation,
                                          int bits_per_symbol)
{
    for (size_t i = 0; i < input->size(); ++i)
    {
        complex<double> received = (*input)[i];
        int best_index = 0;
        double min_dist = numeric_limits<double>::max();

        // Ищем точку созвездия с минимальным расстоянием до принятой
        for (int j = 0; j < (1 << bits_per_symbol); ++j)
        {

            double dist = pow(abs(received - constellation[j]), 2);
            if (dist < min_dist)
            {
                min_dist = dist;
                best_index = j;
            }
        }

        for (int b = 0; b < bits_per_symbol; ++b)
        {
            (*output)[i * bits_per_symbol + (bits_per_symbol - 1 - b)] = (best_index >> b) & 1;
        }
    }
}
