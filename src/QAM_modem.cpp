#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"
#include <stdexcept>

std::vector<sample> QAM_base::generate_constellation(const mod_type& type){
    int const M = int(type);

    const int bits_per_symbol = std::log2(M);

    std::vector<sample> constellation(M);

    sample symbol;
    std::vector<int8_t> bits;

    float I, Q, coeff;

    // fill constellation
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
        else{
            logger->error("Invalid modulation type: {}!", M);
            return {};
        }

        constellation[i] = symbol;
    }
    
    return constellation;
}

std::vector<sample> QAM_modulator::QAM_modulation(const std::vector<int8_t>& bits, const mod_type& type){

    const int M = type;

    std::vector<sample> constellation = constellations[M];

    const int bits_per_symbol = std::log2(M);

    std::vector<sample> result(bits.size() / bits_per_symbol);

    std::vector<int8_t> symbol_bits(bits_per_symbol);

    int index = 0;
    int k = 0;
    for(int i = 0; i < bits.size(); i += bits_per_symbol){

        for(int j = 0; j < bits_per_symbol; ++j){
            symbol_bits[j] = bits[i + j];
        }

        index = bin_to_dec(symbol_bits);

        result[k++] = constellation[index];
    }

    return result;
}


std::vector<int8_t> QAM_demodulator::QAM_soft_demodulation(const std::vector<sample>& symbols, const mod_type& type){

    const int M = type;
    
    std::vector<sample> constellation = constellations[M];

    int bits_per_symbol = std::log2(M);

    std::vector<int8_t> bits;
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

std::vector<int8_t> QAM_demodulator::QAM_hard_demodulation(const std::vector<sample>& symbols, const mod_type& M){
    if(M == QPSK){
        return QPSK_hard_demodulation(symbols);
    }
    else if(M == QAM16){
        return QAM16_hard_demodulation(symbols);
    }
    else if(M == QAM64){
        return QAM64_hard_demodulation(symbols);
    }
    else{
        logger->error("[QAM_modem.cpp:QAM_hard_demodulation]: Invalid type of modulation! Try 2, 4, 16!");
        return {};
    }
}


std::vector<int8_t> QAM_demodulator::QPSK_hard_demodulation(const std::vector<sample>& symbols){
    std::vector<int8_t> result(symbols.size() * 2);

    for (int i = 0; i < symbols.size(); ++i) {
        double I = symbols[i].real();
        double Q = symbols[i].imag();

        result[2 * i] = I > 0 ? 0 : 1;

        result[2 * i + 1] = Q > 0 ? 0 : 1;
    }

    return result;

}

std::vector<int8_t> QAM_demodulator::QAM16_hard_demodulation(const std::vector<sample>& symbols){

    std::vector<int8_t> result(symbols.size() * 4);

  for (int i = 0; i < symbols.size(); ++i) {

    double I = symbols[i].real();
    double Q = symbols[i].imag();

    if (I > 0) {
      result[4 * i] = 0;
    } 
    else {
      result[4 * i] = 1;
    }

    if ((I > QAM16_THRESHOLD) || ( I < -QAM16_THRESHOLD)) {
      result[4 * i + 2] = 1;
    } 
    else {
      result[4 * i + 2] = 0;
    }

    if (Q > 0) {
      result[4 * i + 1] = 0;
    } 
    else {
      result[4 * i + 1] = 1;
    }

    if ((Q > QAM16_THRESHOLD) || (Q < -QAM16_THRESHOLD)) {
      result[4 * i + 3] = 1;
    } 
    else {
      result[4 * i + 3] = 0;
    }
  }

    return result;

}


std::vector<int8_t> QAM_demodulator::QAM64_hard_demodulation(const std::vector<sample>& symbols) {
    std::vector<int8_t> result(symbols.size() * 6);

    for (int i = 0; i < symbols.size(); ++i) {
        double I = symbols[i].real();
        double Q = symbols[i].imag();

        if (I > 0) {
            result[6 * i] = 0;
        } else {
            result[6 * i] = 1;
        }

        if (I > QAM64_THRESHOLD_3 || I < -QAM64_THRESHOLD_3) {
            result[6 * i + 2] = 1;
            result[6 * i + 4] = 1;
        } 
        else if (I > QAM64_THRESHOLD_2 || I < -QAM64_THRESHOLD_2) {
            result[6 * i + 2] = 1;
            result[6 * i + 4] = 0;
        } 
        else if (I > QAM64_THRESHOLD_1 || I < -QAM64_THRESHOLD_1) {
            result[6 * i + 2] = 0;
            result[6 * i + 4] = 0;
        } 
        else {
            result[6 * i + 2] = 0;
            result[6 * i + 4] = 1;
        }

        if (Q > 0) {
            result[6 * i + 1] = 0;
        } 
        else {
            result[6 * i + 1] = 1;
        }

        if (Q > QAM64_THRESHOLD_3 || Q < -QAM64_THRESHOLD_3) {
            result[6 * i + 3] = 1;
            result[6 * i + 5] = 1;
        } 
        else if (Q > QAM64_THRESHOLD_2 || Q < -QAM64_THRESHOLD_2) {
            result[6 * i + 3] = 1;
            result[6 * i + 5] = 0;
        } 
        else if (Q > QAM64_THRESHOLD_1 || Q < -QAM64_THRESHOLD_1) {
            result[6 * i + 3] = 0;
            result[6 * i + 5] = 0;
        } 
        else {
            result[6 * i + 3] = 0;
            result[6 * i + 5] = 1;
        }
    }

    return result;
}