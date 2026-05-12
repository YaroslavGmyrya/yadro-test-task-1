#include "../include/sub_func.hpp"
#include <spdlog/spdlog.h>

std::vector<int8_t> generate_bits(const uint& N){
    std::vector<int8_t> bits;
    bits.reserve(N);

    for(int i = 0; i < N; ++i){
        bits.push_back(rand() % 2);
    }

    return bits;
}


std::vector<int8_t> dec_to_bin(const uint& num, const uint& size){
    std::vector<int8_t> bits(size);

    for(int i = size-1; i >= 0; --i){
        bits[size-1-i] = (num >> i) & 1;
    }

    return bits;
}

int bin_to_dec(const std::vector<int8_t>& bits){
    int num = 0;

    for(int i = 0; i < bits.size(); ++i){
        num |= bits[i] << (bits.size() - 1 - i);
    }

    return num;
}

float calculate_ber(const std::vector<int8_t>& tx_bits, const std::vector<int8_t>& rx_bits){
    if(tx_bits.size() != rx_bits.size()){
        spdlog::error("Error: Size of TX and RX bits do not match!");
        return -1;
    }

    float error_count = 0;

    for(int i = 0; i < tx_bits.size(); ++i){
        if(tx_bits[i] != rx_bits[i]){
            error_count++;
        }
    }

    return error_count / tx_bits.size();
}

float Q(const float& x) {
    return 0.5 * std::erfc(x / std::sqrt(2));
}

std::vector<float> QAM_theoretical_ber(const std::vector<float>& EbN0_dB, const int& M)
{
    std::vector<float> result;
    result.reserve(EbN0_dB.size());

    float k = std::log2(M);

    float coeff = (4.0 / k) * (1.0 - 1.0 / std::sqrt(M));

    for(const float& snr_dB : EbN0_dB)
    {
        float EbN0 = std::pow(10.0, snr_dB / 10.0);

        float x = std::sqrt((3.0 * k / (M - 1.0)) * EbN0);

        result.push_back(coeff * Q(x));
    }

    return result;
}

float EbN0_to_N0(const float& EbN0, const int& M){
    // energy per symbol (I use normalized symbols, beacause Es = 1)
    float Es = 1;

    // energy per bit. If symbol constain N bits, then Eb = Es / N, N = log2(M)
    float Eb = Es / std::log2(M);

    float lin_EbN0;

    lin_EbN0 = pow(10.0, EbN0 / 10.0);

    return Eb / lin_EbN0;
}