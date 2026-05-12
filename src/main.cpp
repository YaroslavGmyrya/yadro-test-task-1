#include <iostream>

#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"
#include "../include/channel.hpp"
#include "../include/sub_func.hpp"
#include "../include/simulation.hpp"
#include "../include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main(){
    // 1. Create config
    sim_config config;
    config.M = {QPSK, QAM16, QAM64};
    config.N = 60000;
    config.REALIZATIONS = 40;

    config.MIN_EbN0 = 0;
    config.MAX_EbN0 = 20;
    config.STEP_EbN0 = 0.5;

    config.demod_type = "soft";

    // 2.Run simulation
    sim_out results;
    results = run_simulation(config);

    // 3. Compute theoretical BER (EbN0 axis)
    std::vector<std::vector<float>> theor_ber(config.M.size());
    for(int i = 0; i < theor_ber.size(); ++i){
        theor_ber[i] = QAM_theoretical_ber(results.EbN0_axis, config.M[i]);
    }

    // 4. Plot emperical/theoretical BER (disperssion axis)
    for(int i = 0; i < config.M.size(); ++i){
        int m = config.M[i];
        plt::named_semilogy("Emperical QAM"+std::to_string(m)+" BER", results.EbN0_axis, results.BER[i], "--");
        plt::named_semilogy("Theoretical QAM"+std::to_string(m)+" BER", results.EbN0_axis, theor_ber[i]);
    }

    plt::xlabel("EbN0");
    plt::ylabel("BER");
    plt::title("BER(EbN0)");
    plt::grid(true);
    plt::legend();
    plt::ylim(1e-6, 1.0);
    plt::show();

    // 5. Plot emperical/theoretical BER (disperssion axis)
    for(int i = 0; i < config.M.size(); ++i){
        int m = config.M[i];
        plt::named_semilogy("Emperical QAM"+std::to_string(m)+" BER", results.disp_axis[i], results.BER[i], "--");
        plt::named_semilogy("Theoretical QAM"+std::to_string(m)+" BER", results.disp_axis[i], theor_ber[i]);
    }

    plt::xlabel("N0");
    plt::ylabel("BER");
    plt::title("BER(N0)");
    plt::grid(true);
    plt::legend();
    plt::ylim(1e-6, 1.0);
    plt::show();

    return 0;
}