#include "../include/channel.hpp"
#include "../include/sub_func.hpp"

std::vector<sample> channel::AWGN(const std::vector<sample> &samples, const float& EbN0, const int& M)
{
    // noise spectral density
    float N0 = EbN0_to_N0(EbN0, M);

    // noise disperssion
    float sigma = std::sqrt(N0 / 2);

    // set generator parameters
    std::normal_distribution<float> dist(0, sigma);
    std::vector<sample> result(samples.size());

    for (int i = 0; i < samples.size(); ++i)
    {
        result[i] = samples[i] + sample(dist(gen), dist(gen));
    }

    return result;
}
