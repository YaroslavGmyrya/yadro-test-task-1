#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"
#include "../include/channel.hpp"
#include "../include/sub_func.hpp"

int main(){

    // Model parameters
    const int M = 4; // 4, 16, 64
    const int N = 1000; // Count of bits
    const int SNR = 20; // Signal Noise Ratio (db)

    // 1. Generate bits
    std::vector<int8_t> tx_bits = generate_bits(N);

    // 2. Generate symbols
    QAM_modulator modulator;
    std::vector<sample> tx_symbols = modulator.QAM_modulation(tx_bits, M);


    // 3. AWGN
        channel ch;
        std::vector<sample> rx_symbols = ch.AWGN(tx_symbols, SNR);

    // 4. Demodulation
        QAM_demodulator demodulator;
        std::vector<int8_t> rx_bits = demodulator.QAM_demodulation(M, rx_symbols);


    // 5. Calculate BER
    float ber = calculate_ber(tx_bits, rx_bits);
    std::cout << "BER: " << ber << std::endl;

    // // 5. Write to files
    // write_to_file<int8_t>("../pcm/bits.pcm", bits);
    // write_to_file<sample>("../pcm/tx_symbols.pcm", tx_symbols);
    // write_to_file<sample>("../pcm/rx_symbols.pcm", rx_symbols);

    return 0;
}