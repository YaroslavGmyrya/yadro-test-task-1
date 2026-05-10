#include "../include/channel.hpp"

std::vector<sample> channel::AWGN(const std::vector<sample> &samples, const float& SNR, const int& M)
{
    // calculate power per symbol
    float mean_Es = 0;
    for (const sample& el : samples){
        mean_Es += std::norm(el);
    }
    mean_Es /= samples.size();

    // noise dispersion
    float bits_per_symbol = std::log2(M);
    float lin_SNR = std::pow(10, SNR / 10);

    // energy per bit
    float E_b = mean_Es / bits_per_symbol;
    
    // spectral noise density
    float N0 = E_b / lin_SNR;

    // noise dispersion
    float sigma = std::sqrt(N0 / 2);

    // create generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // set parameters
    std::normal_distribution<float> dist(0, sigma);
    
    std::vector<sample> result(samples.size());

    for (int i = 0; i < samples.size(); ++i)
    {
        result[i] = samples[i] + sample(dist(gen), dist(gen));
    }

    return result;
}