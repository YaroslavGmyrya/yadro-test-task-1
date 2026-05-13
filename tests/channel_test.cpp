#include "../include/QAM_modem.hpp"
#include "../include/channel.hpp"
#include "../include/sub_func.hpp"
#include "../include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int CHANNEL_TEST(){
    QAM_modulator modulator;
    channel ch;

    const double EbN0 = 20;
    const int N = 6000;

    std::vector<uint8_t> bits = generate_bits(N);

    std::vector<sample> symbols;
    
    std::vector<double> I;
    std::vector<double> Q;

    for(const mod_type& el : allowed_modulations){
        I.clear();
        Q.clear();

        symbols = modulator.QAM_modulation(bits, el);
        symbols = ch.AWGN(symbols, EbN0, el);

        for(const sample& point : symbols){
            I.push_back(point.real());
            Q.push_back(point.imag());
        }

        plt::scatter(I, Q, 150);
        plt::xlabel("I");
        plt::ylabel("Q");
        plt::title(std::to_string(el) + "-" + "QAM constellation on RX, EbN0 = " + std::to_string(EbN0));
        plt::show();


    }

    return 0;  
}
