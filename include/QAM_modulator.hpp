#pragma once

#include <iostream>
#include <complex>
#include <vector>
#include <spdlog/spdlog.h>

#define DEBUG 0

using sample = std::complex<float>;

class QAM_modulator{
    public:
        std::vector<sample> QAM_modulation(const int& mod_order, const std::vector<int8_t>& bits);

    private:
        std::vector<sample> QPSK_modulation(const std::vector<int8_t>& bits);
        std::vector<sample> QAM16_modulation(const std::vector<int8_t>& bits);
        std::vector<sample> QAM64_modulation(const std::vector<int8_t>& bits);

};