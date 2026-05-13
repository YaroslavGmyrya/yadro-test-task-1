#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

std::vector<uint8_t> generate_bits(const uint& N);
std::vector<uint8_t> dec_to_bin(const uint& num, const uint& size);
int bin_to_dec(const std::vector<uint8_t>& bits);

float calculate_ber(const std::vector<uint8_t>& tx_bits, const std::vector<uint8_t>& rx_bits);

float Q(const float& x);
float EbN0_to_N0(const float& EbN0, const int& M);
std::vector<float> QAM_theoretical_ber(const std::vector<float>& EbN0_dB, const int& M);
