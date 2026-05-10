#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"
#include "../include/channel.hpp"
#include "../include/sub_func.hpp"

int main(){

    // Model parameters
    std::vector<int> M = {4, 16, 64};
    const int N = 102000; // Count of bits

    const float MIN_SNR = 0;
    const float MAX_SNR = 19;
    const float STEP_SNR = 0.5;

    std::vector<float> SNRs; //SNR sets (dB)
    for(float i = MIN_SNR; i <= MAX_SNR; i += STEP_SNR){
        SNRs.push_back(i);
    }

    const int REALIZATIONS = 100; // Count of realizations for each SNR

    // Create objects
    QAM_demodulator demodulator;
    QAM_modulator modulator;
    channel ch;

    std::vector<int8_t> tx_bits;
    std::vector<sample> tx_symbols;
    std::vector<sample> rx_symbols;
    std::vector<int8_t> rx_bits;
    std::string filename;

    float BER;

    std::vector<sample> SNR_snd_BER;
    SNR_snd_BER.reserve(SNRs.size());

    // iterate on modulation order
    for(const int& m : M){
        SNR_snd_BER.clear();

        // iterate on SNR
        for(const float& SNR : SNRs){
            BER = 0;
            for(int i = 0; i < REALIZATIONS; ++i){
                // 1. Generate bits
                tx_bits = generate_bits(N);
        
                // 2. Generate symbols
                tx_symbols = modulator.QAM_modulation(tx_bits, m);
        
                // 3. AWGN
                rx_symbols = ch.AWGN(tx_symbols, SNR, m);
        
                // 4. Demodulation
                rx_bits = demodulator.QAM_demodulation(m, rx_symbols);
        
                // 5. Calculate BER
                BER += calculate_ber(tx_bits, rx_bits);
            }

            SNR_snd_BER.push_back(sample(SNR, BER / REALIZATIONS));
        }

        filename = "../pcm/SNR_BER_QAM_" + std::to_string(m) + ".pcm";

        write_to_file<sample>(filename.data(), SNR_snd_BER);
    }

    return 0;
}