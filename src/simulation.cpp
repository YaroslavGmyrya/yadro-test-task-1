#include "../include/simulation.hpp"
#include "../include/QAM_modem.hpp"
#include "../include/channel.hpp"
#include "../include/sub_func.hpp"

sim_out run_simulation(const sim_config& config){

    // output struct
    sim_out results;

    // create axis
    results.disp_axis.resize(config.M.size());
    for(float EbN0 = config.MIN_EbN0; EbN0 <= config.MAX_EbN0; EbN0 += config.STEP_EbN0){
        results.EbN0_axis.push_back(EbN0);

        for(int m = 0; m < config.M.size(); ++m){
            results.disp_axis[m].push_back(EbN0_to_N0(EbN0, config.M[m]));
        }
    }

    // Create objects
    QAM_demodulator demodulator;
    QAM_modulator modulator;
    channel ch;


    results.BER.resize(config.M.size());

    // start simulation
    int j = 0;
    for(const mod_type& modulation_type : config.M){
        for(const float& EbN0 : results.EbN0_axis){
            float BER_counter = 0;

            for(int i = 0; i < config.REALIZATIONS; ++i){
                // 1. Generate bits
                std::vector<int8_t> tx_bits = generate_bits(config.N);
    
                // 2. Generate symbols
                std::vector<sample> tx_symbols = modulator.QAM_modulation(tx_bits, modulation_type);
        
                // 3. AWGN
                std::vector<sample> rx_symbols = ch.AWGN(tx_symbols, EbN0, (int)modulation_type);

                // 4. Demodulation
                std::vector<int8_t> rx_bits;

                if(config.demod_type == "soft")
                   rx_bits = demodulator.QAM_soft_demodulation(rx_symbols, modulation_type);
                else
                   rx_bits = demodulator.QAM_hard_demodulation(rx_symbols, modulation_type);
        
                // 5. Calculate BER
                BER_counter += calculate_ber(tx_bits, rx_bits);
            }

            results.BER[j].push_back(BER_counter / config.REALIZATIONS);
        }

        j++;
    }

    return results;
}