#include "../include/QAM_modem.hpp"
#include "../include/sub_func.hpp"

int TEST_QAM_CONSTELLATION(){
    QAM_modulator modulator;

    std::vector<sample> QPSK_constellation = generate_constellation(4);
    std::vector<sample> QAM16_constellation = generate_constellation(16);
    std::vector<sample> QAM64_constellation = generate_constellation(64);

    write_to_file<sample>("../pcm/QPSK_constellation.pcm", QPSK_constellation);
    write_to_file<sample>("../pcm/QAM16_constellation.pcm", QAM16_constellation);
    write_to_file<sample>("../pcm/QAM64_constellation.pcm", QAM64_constellation);

    return 0;  
}