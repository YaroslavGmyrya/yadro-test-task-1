#include "../include/channel.hpp"

std::vector<sample> channel::AWGN(std::vector<sample> &samples, float SNR)
{
    // calculate signal power
    float mean_Es = 0;
    for (const sample& el : samples){
        mean_Es += std::norm(el);
    }

    // mean power
    mean_Es /= samples.size();

    // noise dispersion
    float lin_SNR = std::pow(10, SNR / 10);
    float E_n = mean_Es / lin_SNR;
    float sigma = std::sqrt(E_n / 2);

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