 #pragma once

#include <vector>
#include <complex>
#include <random>

using sample = std::complex<float>;

class channel{
    public:
        // Add Additive White Gaussian Noise (AWGN) to signal. SNR - Signal Noise Ratio (db)
        std::vector<sample> AWGN(const std::vector<sample> &samples, const float& SNR, const int& M);
};
