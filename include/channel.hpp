#pragma once

#include <vector>
#include <complex>
#include <random>

using sample = std::complex<float>;

class channel{
    public:

        channel() : gen(std::random_device{}()) {}

        // Add Additive White Gaussian Noise (AWGN) to signal
        std::vector<sample> AWGN(const std::vector<sample> &samples, const float& EbN0, const int& M);

    private:
        std::mt19937 gen;
};
