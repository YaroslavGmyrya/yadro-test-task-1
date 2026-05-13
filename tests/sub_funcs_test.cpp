#include "../include/sub_func.hpp"
#include <spdlog/spdlog.h>

// Generate random bits and check size, values of result
int GENERATE_BITS_TEST(){
    const uint N = 10;
    std::vector<uint8_t> bits = generate_bits(N);

    int error = 0;

    // if invalid size
    if(bits.size() != N){
        spdlog::error("[GENERATE_BITS_TEST]: Invalid size of bits!");
        error = 1;
    }

    // if invalid values
    for(const uint8_t& el : bits){
        if(el != 0 && el != 1){
            spdlog::error("[GENERATE_BITS_TEST]: Invalid value in bits! Bit should be 0 or 1!");
            error = 1;
        }
    }

    return error;
}

// Translate decimal number to binary, check size, values of result and compare with expected bits
int DEC_TO_BIN_TEST(){
    const int num = 10;
    const int size = 4;
    int error = 0;

    std::vector<uint8_t> bits = dec_to_bin(num, size);
    std::vector<uint8_t> expected_bits = {1, 0, 1, 0};


    // if invalid size
    if(bits.size() != size){
        spdlog::error("[DEC_TO_BIN_TEST]: Invalid size of bits!");
        error = 1;
    }

    // if invalid values
    for(const uint8_t& el : bits){
        if(el != 0 && el != 1){
            spdlog::error("[DEC_TO_BIN_TEST]: Invalid value in bits! Bit should be 0 or 1!");
            error = 1;
        }
    }

    // if bad answer   
    if(bits != expected_bits){
        spdlog::error("[DEC_TO_BIN_TEST]: Result does not match expected bits!");
        error = 1;
    }
    return error;
}

// Translate binary number to decimal, check values of result and compare with expected number
int BIN_TO_DEC_TEST(){
    std::vector<uint8_t> bits = {1, 0, 1, 0};
    const int expected_num = 10;
    int error = 0;

    int num = bin_to_dec(bits);

    // if bad answer   
    if(num != expected_num){
        spdlog::error("[BIN_TO_DEC_TEST]: Result does not match expected number!");
        error = 1;
    }
    
    return error;
}