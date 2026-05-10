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
using complex_signal = vector<complex<double>>;

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
    {1.0 / sqrt(10), 1.0 / sqrt(10)},   // 0000
    {-1.0 / sqrt(10), 1.0 / sqrt(10)},  // 0001
    {-1.0 / sqrt(10), -1.0 / sqrt(10)}, // 0011
    {1.0 / sqrt(10), -1.0 / sqrt(10)},  // 0010
    {3.0 / sqrt(10), 3.0 / sqrt(10)},   // 0100
    {-3.0 / sqrt(10), 3.0 / sqrt(10)},  // 0101
    {-3.0 / sqrt(10), -3.0 / sqrt(10)}, // 0111
    {3.0 / sqrt(10), -3.0 / sqrt(10)},  // 0110
    {1.0 / sqrt(10), 3.0 / sqrt(10)},   // 1000
    {-1.0 / sqrt(10), 3.0 / sqrt(10)},  // 1001
    {-1.0 / sqrt(10), -3.0 / sqrt(10)}, // 1011
    {1.0 / sqrt(10), -3.0 / sqrt(10)},  // 1010
    {3.0 / sqrt(10), 1.0 / sqrt(10)},   // 1100
    {-3.0 / sqrt(10), 1.0 / sqrt(10)},  // 1101
    {-3.0 / sqrt(10), -1.0 / sqrt(10)}, // 1111
    {3.0 / sqrt(10), -1.0 / sqrt(10)}   // 1110
};

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