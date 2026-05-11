#include "../include/channel.hpp"
#include "../include/sub_func.hpp"
#include "../include/QAM_modem.hpp"

int AWGN_TEST(){
    const int N = 36000;
    float SNR = 24;
    std::vector<int> M = {4, 16, 64};

    QAM_modulator modulator;
    channel ch;

    std::vector<int8_t> bits = generate_bits(N);

    std::vector<sample> samples;
    std::vector<sample> noisy_samples;
    std::string filename;

    int error = 0;

    for(const int& m : M){
        samples = modulator.QAM_modulation(bits, m);

        if(samples.size() == 0){
            error = 1;
            continue;
        }

        noisy_samples = ch.AWGN(samples, SNR, m);

        filename = "../pcm/NOISLY_" + std::to_string(m) + "_SAMPLES.pcm";
        write_to_file<sample>(filename.data(), noisy_samples);
    }

    return error;

}