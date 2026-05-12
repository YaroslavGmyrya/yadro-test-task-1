#pragma once

#include <vector>
#include "../include/QAM_modem.hpp"

struct sim_config {
    std::vector<mod_type> M;     // allowed modulations

    int N;                  // Count of bits
    int REALIZATIONS;       // Count of realizations for each SNR

    // EbN0 is ratio of energy per bit and spectral density power
    float MIN_EbN0;
    float MAX_EbN0;
    float STEP_EbN0;

    std::string demod_type;     // hard or soft
};

struct sim_out {
    std::vector<float> EbN0_axis;
    std::vector<std::vector<float>> disp_axis;
    std::vector<std::vector<float>> BER;
};

sim_out run_simulation(const sim_config& config);