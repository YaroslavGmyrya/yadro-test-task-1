#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"

std::vector<sample> generate_constellation(const int& M){

    if(M != 4 && M != 16 && M != 64){
        spdlog::error("[QAM_modem.cpp:generate_constellation]: Invalid modulation order. Try 4, 16, 64!");
        return {};
    }

    const int bits_per_symbol = std::log2(M);

    std::vector<sample> constellation;
    constellation.reserve(M);

    // fill constellation
    sample symbol;
    std::vector<int8_t> bits;

    float I, Q, coeff;

    for(int i = 0; i < M; ++i){
        bits = dec_to_bin(i, bits_per_symbol);

        // if QPSK
        if(M == 4){
            coeff = 1 / std::sqrt(2);
            I = (1 - 2*bits[0]) * coeff;
            Q = (1 - 2*bits[1]) * coeff;
            symbol = sample(I, Q);
        }

        // if QAM16
        else if(M == 16){
            coeff = 1.0 / std::sqrt(10);
            I = ( (1 - 2*bits[0]) * (2 - (1 - 2*bits[2])) ) * coeff;
            Q = ( (1 - 2*bits[1]) * (2 - (1 - 2*bits[3])) ) * coeff;
            symbol = sample(I, Q);
        }
    
        // if QAM64
        else if(M == 64){
            coeff = 1.0 / std::sqrt(42);
            I = (1 - 2*bits[0]) * (4 - (1 - 2*bits[2]) * (2 - (1 - 2*bits[4]))) * coeff;
            Q = (1 - 2*bits[1]) * (4 - (1 - 2*bits[3]) * (2 - (1 - 2*bits[5]))) * coeff;
            symbol = sample(I, Q);
        }

        constellation.push_back(symbol);
    }
    
    return constellation;

}

std::vector<sample> QAM_modulator::QAM_modulation(const std::vector<int8_t>& bits, const int& M){
    std::vector<sample> constellation;

    if(M == 4){
        constellation = qpsk_constellation;
    }
    else if(M == 16){
        constellation = qam16_constellation;
    }
    else if(M == 64){
        constellation = qam64_constellation;
    }

    else{
        logger->error("[QAM_modulator::QAM_modulation]: Invalid modulation order. Try 4, 16, 64!");
        return {};
    }

    const int bits_per_symbol = std::log2(M);

    std::vector<sample> result;
    result.reserve(bits.size() / bits_per_symbol);

    std::vector<int8_t> symbol_bits(bits_per_symbol);

    int index;
    for(int i = 0; i < bits.size(); i += bits_per_symbol){

        for(int j = 0; j < bits_per_symbol; ++j){
            symbol_bits[j] = bits[i + j];
        }

        index = bin_to_dec(symbol_bits);

        result.push_back(constellation[index]);

    }

    return result;
}


std::vector<int8_t> QAM_demodulator::QAM_demodulation(const int& M, const std::vector<sample>& symbols){
    std::vector<sample> constellation;

    if(M == 4){
        constellation = QPSK_constellation;
    }
    else if(M == 16){
        constellation = QAM16_constellation;
    }
    else if(M == 64){
        constellation = QAM64_constellation;
    }
    else{
        logger->error("[QAM_demodulator::QAM_demodulation]: Invalid modulation order. Try 4, 16, 64!");
        return {};
    }

    std::vector<int8_t> bits;
    int bits_per_symbol = std::log2(M);
    bits.reserve(symbols.size() * bits_per_symbol);

    for(int i = 0; i < symbols.size(); ++i){
        float min_distance = std::norm(symbols[i] - constellation[0]);
        float cur_distance;
        int index = 0;

        for(int j = 1; j < constellation.size(); ++j){
            cur_distance = std::norm(symbols[i] - constellation[j]);
            if(cur_distance < min_distance){
                min_distance = cur_distance;
                index = j;
            }
        }

        std::vector<int8_t> symbol_bits = dec_to_bin(index, bits_per_symbol);

        for(const int8_t& bit : symbol_bits){
            bits.push_back(bit);
        }
    }

    return bits;
}