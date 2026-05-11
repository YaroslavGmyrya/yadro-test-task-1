#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"

// Generate all constellation and write to files for testing in PYTHON script (check_consellation.py)
int QAM_CONSTELLATION_TEST(){
    QAM_modulator modulator;

    std::vector<sample> QPSK_constellation = generate_constellation(4);
    std::vector<sample> QAM16_constellation = generate_constellation(16);
    std::vector<sample> QAM64_constellation = generate_constellation(64);

    write_to_file<sample>("../pcm/QPSK_constellation.pcm", QPSK_constellation);
    write_to_file<sample>("../pcm/QAM16_constellation.pcm", QAM16_constellation);
    write_to_file<sample>("../pcm/QAM64_constellation.pcm", QAM64_constellation);

    return 0;  
}

// Generate random bits, modualte, demodulate and calculate BER for all modulation orders (4, 16, 64)
int QAM_MODEM_TEST(){
    QAM_modulator modulator;
    QAM_demodulator demodulator;

    std::vector<int> M = {4, 16, 64};
    
    float error = 0;

    std::vector<int8_t> bits;
    std::vector<sample> symbols;
    std::vector<int8_t> demodulated_bits;

    for(const int& m : M){
        bits = generate_bits(600);
        symbols = modulator.QAM_modulation(bits, m);
        demodulated_bits = demodulator.QAM_demodulation(m, symbols);

        error += calculate_ber(bits, demodulated_bits);
    }

    return error;  
}