#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <complex>
#include <random>
#include <stdexcept>
#include <numeric>
#include <math.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <omp.h>

using namespace std;
using complex_signal = vector<complex<float>>;

enum modulation_type
{
    QPSK,  // 2 bit for symbol
    QAM16, // 4 bit for symbol
    QAM64  // 6 bit for symbol
};

// созвездия по кодам Грея для QPSK, QAM16 и QAM64
inline const complex_signal QPSK_constellation = {
    {1.0 / sqrt(2), 1.0 / sqrt(2)},   // 00
    {-1.0 / sqrt(2), 1.0 / sqrt(2)},  // 01
    {-1.0 / sqrt(2), -1.0 / sqrt(2)}, // 11
    {1.0 / sqrt(2), -1.0 / sqrt(2)}   // 10
};

inline const complex_signal QAM16_constellation = {
    {-3 / sqrt(10.0), -3 / sqrt(10.0)},
    {-3 / sqrt(10.0), -1 / sqrt(10.0)},
    {-3 / sqrt(10.0), 3 / sqrt(10.0)},
    {-3 / sqrt(10.0), 1 / sqrt(10.0)},
    {-1 / sqrt(10.0), -3 / sqrt(10.0)},
    {-1 / sqrt(10.0), -1 / sqrt(10.0)},
    {-1 / sqrt(10.0), 3 / sqrt(10.0)},
    {-1 / sqrt(10.0), 1 / sqrt(10.0)},
    {3 / sqrt(10.0), -3 / sqrt(10.0)},
    {3 / sqrt(10.0), -1 / sqrt(10.0)},
    {3 / sqrt(10.0), 3 / sqrt(10.0)},
    {3 / sqrt(10.0), 1 / sqrt(10.0)},
    {1 / sqrt(10.0), -3 / sqrt(10.0)},
    {1 / sqrt(10.0), -1 / sqrt(10.0)},
    {1 / sqrt(10.0), 3 / sqrt(10.0)},
    {1 / sqrt(10.0), 1 / sqrt(10.0)}};

inline const complex_signal QAM64_constellation = {
    {-7 / sqrt(42.0), -7 / sqrt(42.0)},
    {-7 / sqrt(42.0), -5 / sqrt(42.0)},
    {-7 / sqrt(42.0), -1 / sqrt(42.0)},
    {-7 / sqrt(42.0), -3 / sqrt(42.0)},
    {-7 / sqrt(42.0), 5 / sqrt(42.0)},
    {-7 / sqrt(42.0), 1 / sqrt(42.0)},
    {-7 / sqrt(42.0), 3 / sqrt(42.0)},
    {-7 / sqrt(42.0), 7 / sqrt(42.0)},
    {-5 / sqrt(42.0), -7 / sqrt(42.0)},
    {-5 / sqrt(42.0), -5 / sqrt(42.0)},
    {-5 / sqrt(42.0), -1 / sqrt(42.0)},
    {-5 / sqrt(42.0), -3 / sqrt(42.0)},
    {-5 / sqrt(42.0), 7 / sqrt(42.0)},
    {-5 / sqrt(42.0), 5 / sqrt(42.0)},
    {-5 / sqrt(42.0), 1 / sqrt(42.0)},
    {-5 / sqrt(42.0), 3 / sqrt(42.0)},
    {-1 / sqrt(42.0), -7 / sqrt(42.0)},
    {-1 / sqrt(42.0), -5 / sqrt(42.0)},
    {-1 / sqrt(42.0), -1 / sqrt(42.0)},
    {-1 / sqrt(42.0), -3 / sqrt(42.0)},
    {-1 / sqrt(42.0), 7 / sqrt(42.0)},
    {-1 / sqrt(42.0), 5 / sqrt(42.0)},
    {-1 / sqrt(42.0), 1 / sqrt(42.0)},
    {-1 / sqrt(42.0), 3 / sqrt(42.0)},
    {-3 / sqrt(42.0), -7 / sqrt(42.0)},
    {-3 / sqrt(42.0), -5 / sqrt(42.0)},
    {-3 / sqrt(42.0), -1 / sqrt(42.0)},
    {-3 / sqrt(42.0), -3 / sqrt(42.0)},
    {-3 / sqrt(42.0), 7 / sqrt(42.0)},
    {-3 / sqrt(42.0), 5 / sqrt(42.0)},
    {-3 / sqrt(42.0), 1 / sqrt(42.0)},
    {-3 / sqrt(42.0), 3 / sqrt(42.0)},
    {7 / sqrt(42.0), -7 / sqrt(42.0)},
    {7 / sqrt(42.0), -5 / sqrt(42.0)},
    {7 / sqrt(42.0), -1 / sqrt(42.0)},
    {7 / sqrt(42.0), -3 / sqrt(42.0)},
    {7 / sqrt(42.0), 7 / sqrt(42.0)},
    {7 / sqrt(42.0), 5 / sqrt(42.0)},
    {7 / sqrt(42.0), 1 / sqrt(42.0)},
    {7 / sqrt(42.0), 3 / sqrt(42.0)},
    {5 / sqrt(42.0), -7 / sqrt(42.0)},
    {5 / sqrt(42.0), -5 / sqrt(42.0)},
    {5 / sqrt(42.0), -1 / sqrt(42.0)},
    {5 / sqrt(42.0), -3 / sqrt(42.0)},
    {5 / sqrt(42.0), 7 / sqrt(42.0)},
    {5 / sqrt(42.0), 5 / sqrt(42.0)},
    {5 / sqrt(42.0), 1 / sqrt(42.0)},
    {5 / sqrt(42.0), 3 / sqrt(42.0)},
    {1 / sqrt(42.0), -7 / sqrt(42.0)},
    {1 / sqrt(42.0), -5 / sqrt(42.0)},
    {1 / sqrt(42.0), -1 / sqrt(42.0)},
    {1 / sqrt(42.0), -3 / sqrt(42.0)},
    {1 / sqrt(42.0), 7 / sqrt(42.0)},
    {1 / sqrt(42.0), 5 / sqrt(42.0)},
    {1 / sqrt(42.0), 1 / sqrt(42.0)},
    {1 / sqrt(42.0), 3 / sqrt(42.0)},
    {3 / sqrt(42.0), -7 / sqrt(42.0)},
    {3 / sqrt(42.0), -5 / sqrt(42.0)},
    {3 / sqrt(42.0), -1 / sqrt(42.0)},
    {3 / sqrt(42.0), -3 / sqrt(42.0)},
    {3 / sqrt(42.0), 7 / sqrt(42.0)},
    {3 / sqrt(42.0), 5 / sqrt(42.0)},
    {3 / sqrt(42.0), 1 / sqrt(42.0)},
    {3 / sqrt(42.0), 3 / sqrt(42.0)}};

#endif // UTILS_H