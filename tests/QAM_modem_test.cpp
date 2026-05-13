#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"
#include "../include/matplotlibcpp.h"
#include <bitset>

namespace plt = matplotlibcpp;

// Generate all constellation and write to files for testing in PYTHON script (check_consellation.py)
int QAM_CONSTELLATION_TEST(){
    QAM_modulator modulator;

    std::vector<sample> constellation;
    std::vector<double> I;
    std::vector<double> Q;

    for(const mod_type& el : allowed_modulations){
        int bits_per_symbol = std::log2((int)el);

        I.clear();
        Q.clear();

        constellation = modulator.generate_constellation(el);

        for(int i = 0; i < constellation.size(); ++i){
            I.push_back(constellation[i].real());
            Q.push_back(constellation[i].imag());

            std::string label = std::bitset<6>(i).to_string();
            plt::annotate(label, I[i], Q[i]);
        }

        plt::scatter(I, Q, 150);
        plt::xlabel("I");
        plt::ylabel("Q");
        plt::title(std::to_string(el) + "-" + "QAM constellation on TX");
        plt::show();
    }

    return 0;  
}

// Generate random bits, modualte, demodulate and calculate BER for all modulation orders (4, 16, 64)
int QAM_MODEM_TEST(){
    QAM_modulator modulator;
    QAM_demodulator demodulator;
    
    float error = 0;

    std::vector<uint8_t> bits;
    std::vector<sample> symbols;
    std::vector<uint8_t> demodulated_bits;

    for(const mod_type& m : allowed_modulations){
        bits = generate_bits(600);
        symbols = modulator.QAM_modulation(bits, m);
        demodulated_bits = demodulator.QAM_soft_demodulation(symbols, m);

        error += calculate_ber(bits, demodulated_bits);
    }

    return error;  
}