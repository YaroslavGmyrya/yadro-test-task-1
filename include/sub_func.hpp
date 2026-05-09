#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>


std::vector<int8_t> generate_bits(const uint& N);

std::vector<int8_t> dec_to_bin(const uint& num, const uint& size);

int bin_to_dec(const std::vector<int8_t>& bits);

float calculate_ber(const std::vector<int8_t>& tx_bits, const std::vector<int8_t>& rx_bits);

template<typename T>
void write_to_file(const char* filename, std::vector<T> data) {

    // check size
    if (data.size() == 0) {
        std::cout << "Data is empty!\n";
        return;
    }

    // open file
    std::ofstream file = std::ofstream(filename, std::ios::binary);

    // check file
    if (!file) {
        std::cout << "Error opening file!\n";
        return;
    }

    // write to file
    file.write((char*)data.data(), data.size() * sizeof(T));

    // close file 
    file.close();
}