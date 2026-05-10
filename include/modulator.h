#ifndef MODULATOR_H
#define MODULATOR_H
#include "utils.h"

class Modulator
{
public:
    int bits_per_symbol;
    Modulator(modulation_type mod_type); // Constructor
    complex_signal modulate(const vector<int> &input);

private:
    void modulate_qpsk(const vector<int> &input,
                       complex_signal &output,
                       const complex_signal &constellation);
    void modulate_qam16(const vector<int> &input,
                        complex_signal &output,
                        const complex_signal &constellation);
    void modulate_qam64(const vector<int> &input,
                        complex_signal &output,
                        const complex_signal &constellation);
};
#endif // MODULATOR_H