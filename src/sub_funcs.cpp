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