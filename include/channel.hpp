#pragma once

#include <vector>
#include <complex>
#include <random>

using sample = std::complex<float>;

class channel{
    public:
        std::vector<sample> AWGN(std::vector<sample> &samples, float SNR);
};
