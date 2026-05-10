#include "../include/modulator.h"

Modulator::Modulator(modulation_type mod_type)
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
} // Constructor

complex_signal Modulator::modulate(const vector<int> &input)
{
    complex_signal output(input.size() / bits_per_symbol);
    switch (bits_per_symbol)
    {
    case 2:
        modulate_qpsk(input, output, QPSK_constellation);
        break;
    case 4:
        modulate_qam16(input, output, QAM16_constellation);
        break;
    case 6:
        modulate_qam64(input, output, QAM64_constellation);
        break;
    default:
        throw invalid_argument("Unsupported modulation type");
    }
    return output;
}

void Modulator::modulate_qpsk(const std::vector<int> &input,
                              complex_signal &output,
                              const complex_signal &constellation)
{
    for (size_t i = 0; i < output.size(); ++i)
    {
        // Берем 2 бита и превращаем в индекс 0-3
        int b1 = input[i * 2];
        int b2 = input[i * 2 + 1];
        int index = (b1 << 1) | b2;
        output[i] = constellation[index];
    }
}

void Modulator::modulate_qam16(const std::vector<int> &input,
                               complex_signal &output,
                               const complex_signal &constellation)
{
    for (size_t i = 0; i < output.size(); ++i)
    {
        // Берем 4 бита и превращаем в индекс 0-15
        int index = 0;
        for (int b = 0; b < 4; ++b)
        {
            index = (index << 1) | (input[i * 4 + b] & 1);
        }
        output[i] = constellation[index];
    }
}

void Modulator::modulate_qam64(const std::vector<int> &input,
                               complex_signal &output,
                               const complex_signal &constellation)
{
    for (size_t i = 0; i < output.size(); ++i)
    {
        // Берем 6 бит и превращаем в индекс 0-63
        int index = 0;
        for (int b = 0; b < 6; ++b)
        {
            index = (index << 1) | (input[i * 6 + b] & 1);
        }
        output[i] = constellation[index];
    }
}
