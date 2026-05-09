#include "../include/QAM_modulator.hpp"

std::vector<sample> QAM_modulator::QAM_modulation(const int& mod_order, const std::vector<int8_t>& bits){

    // check input data
    if(bits.empty()){
        if(DEBUG){
            spdlog::error("[QAM_modulator::QAM_modulation]: Input bits vector is empty!");
        }
        return {};
    }

    for(int i = 0; i < bits.size(); ++i){
        if(bits[i] != 0 && bits[i] != 1){
            if(DEBUG){
                spdlog::error("[QAM_modulator::QAM_modulation]: Invalid value in input bits! Bits must be 0 or 1!");
            }
            return {};
        }
    }

    if(mod_order == 4){
        return QPSK_modulation(bits);
    }
    else if(mod_order == 16){
        return QAM16_modulation(bits);
    }
    else if(mod_order == 64){
        return QAM64_modulation(bits);
    }

    if(DEBUG){
        spdlog::error("[QAM_modulator::QAM_modulation]: Invalid modulation order. Try 4, 16, 64!");
    }
    return {};
}

std::vector<sample> QAM_modulator::QPSK_modulation(const std::vector<int8_t>& bits){
    // check size
    if(bits.size() % 2 != 0){
        if(DEBUG){
            spdlog::error("[QAM_modulator::QPSK_modulation]: Invalid bits size! Size must be a multiple of 2!");
        }
        return {};
    }

    // QPSK symbol = 2 bits
    int symbols_count = bits.size() / 2;
    std::vector<sample> symbols;
    symbols.reserve(symbols_count);

    double I,Q;

    // Coefficient for energy normalization
    double coeff = 1 / std::sqrt(2);

    for(int i = 0; i <= bits.size() - 1; i+=2){
        I = (1 - 2*bits[i]) * coeff;
        Q = (1 - 2*bits[i+1]) * coeff;

        symbols.push_back(sample(I,Q));
    }

    return symbols;
}

std::vector<sample> QAM_modulator::QAM16_modulation(const std::vector<int8_t>& bits){
    // check size
    if(bits.size() % 4 != 0){
        if(DEBUG){
            spdlog::error("[QAM_modulator::QAM16_modulation] Invalid bits size! Size must be a multiple of 4!");
        }
        return {};
    }

    // QAM16 symbol = 4 bits
    int symbols_count = bits.size() / 4;
    std::vector<sample> symbols;
    symbols.reserve(symbols_count);

    double I,Q;

    // Coefficient for energy normalization
    double coeff = 1.0 / std::sqrt(10);

    for(int i = 0; i < bits.size(); i += 4){
        I = ( (1 - 2*bits[i]) * (2 - (1 - 2*bits[i+2])) ) * coeff;
        Q = ( (1 - 2*bits[i+1]) * (2 - (1 - 2*bits[i+3])) ) * coeff;

        symbols.push_back(sample(I, Q));
    }


    return symbols;
}

std::vector<sample> QAM_modulator::QAM64_modulation(const std::vector<int8_t>& bits){
    // check size
    if(bits.size() % 6 != 0){
        if(DEBUG){
            spdlog::error("[QAM_modulator::QAM64_modulation]: Invalid bits size! Size must be a multiple of 6!");
        }
        return {};
    }

    // QAM64 symbol = 6 bits
    int symbols_count = bits.size() / 6;
    std::vector<sample> symbols;
    symbols.reserve(symbols_count);

    double I,Q;

    // Coefficient for energy normalization
    double coeff = 1.0 / std::sqrt(42);

    for(int i = 0; i < bits.size(); i += 6){

    I = (1 - 2*bits[i]) * (4 - (1 - 2*bits[i+2]) * (2 - (1 - 2*bits[i+4]))) * coeff;
    Q = (1 - 2*bits[i+1]) * (4 - (1 - 2*bits[i+3]) * (2 - (1 - 2*bits[i+5]))) * coeff;
    
    symbols.push_back(sample(I, Q));
}

    return symbols;
}