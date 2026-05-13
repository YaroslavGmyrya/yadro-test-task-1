#include <iostream>
#include <chrono>

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
    config.REALIZATIONS = 10;

    config.MIN_EbN0 = 0;
    config.MAX_EbN0 = 19;
    config.STEP_EbN0 = 0.5;

    config.demod_type = "hard";     // "hard" or "soft"

    // 2.Run simulation
    auto start = std::chrono::steady_clock::now();
    sim_out results = run_simulation(config);
    auto end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    spdlog::info("Model work {}ms", diff);

    // 3. Compute theoretical BER
    std::unordered_map<mod_type, std::vector<float>> theor_ber;
    for(const mod_type type : config.M){
        theor_ber[type] = QAM_theoretical_ber(results.EbN0_axis, (int)type);
    }

    // 4. Plot emperical/theoretical BER (disperssion axis)
    for(const mod_type& type : config.M){
        plt::named_semilogy("Emperical QAM"+std::to_string((int)type)+" BER", results.EbN0_axis, results.BER[type], "--");
        plt::named_semilogy("Theoretical QAM"+std::to_string((int)type)+" BER", results.EbN0_axis, theor_ber[type]);
    }

    plt::xlabel("EbN0");
    plt::ylabel("BER");
    plt::title("BER(EbN0)");
    plt::grid(true);
    plt::legend();
    plt::ylim(1e-6, 1.0);
    plt::show();

    // 5. Plot emperical/theoretical BER (disperssion axis)
    for(const mod_type& type : config.M){
        plt::named_semilogy("Emperical QAM"+std::to_string((int)type)+" BER", results.disp_axis[type], results.BER[type], "--");
        plt::named_semilogy("Theoretical QAM"+std::to_string((int)type)+" BER", results.disp_axis[type], theor_ber[type]);
    }

    plt::xlabel("N0");
    plt::ylabel("BER");
    plt::title("BER(N0)");
    plt::grid(true);
    plt::legend();
    plt::ylim(1e-6, 1.0);
    plt::show();

    // 6. Compute MSE bw theoretical and emperical BER. Hard demodulation VS Soft demodulation

    for(const mod_type& type : config.M){
        std::vector<float> emp_ber = results.BER[type];
        std::vector<float> theor = theor_ber[type];
    
        float mse_counter = 0;

        for(int i = 0; i < emp_ber.size(); ++i){
            mse_counter += std::pow((emp_ber[i] - theor[i]), 2);
        }

        spdlog::info("QAM-{} MSE Theoretical Vs Emperical BER {} demodulation: {}", (int)type, config.demod_type, mse_counter);
    }

    return 0;
}