#ifndef DEMODULATOR_H
#define DEMODULATOR_H
#include "utils.h"

class Demodulator
{
public:
    Demodulator(modulation_type mod_type); // Constructor
    vector<int> demodulate(const complex_signal *input);

private:
    void demodulate_qpsk(const complex_signal *input,
                         vector<int> *output,
                         const complex_signal &constellation);
    void demodulate_qam16(const complex_signal *input,
                          vector<int> *output,
                          const complex_signal &constellation);
    void demodulate_qam64(const complex_signal *input,
                          vector<int> *output,
                          const complex_signal &constellation);
    void find_nearest_and_decode(const complex_signal *input,
                                 vector<int> *output,
                                 const complex_signal &constellation,
                                 int bits_per_symbol);
};

#endif // DEMODULATOR_H