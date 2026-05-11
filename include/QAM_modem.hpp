#include <iostream>
#include <complex>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

using sample = std::complex<float>;

std::vector<sample> generate_constellation(const int& M);

class QAM_modulator{
    public:
        QAM_modulator(){
            // create logger
            logger = spdlog::get("file_logger");

            if(!logger){
                logger = spdlog::basic_logger_mt("file_logger", "../logs.txt");
            }

            // generate constellations
            qpsk_constellation = generate_constellation(4);
            qam16_constellation = generate_constellation(16);
            qam64_constellation = generate_constellation(64);
        }

        // Modulate bits to symbols. M - count of point in constellation (4, 16, 64)
        std::vector<sample> QAM_modulation(const std::vector<int8_t>& bits, const int& M);

    private:
        std::shared_ptr<spdlog::logger> logger;
        std::vector<sample> qpsk_constellation;
        std::vector<sample> qam16_constellation;
        std::vector<sample> qam64_constellation;
};


using sample = std::complex<float>;

class QAM_demodulator{    
    public:
        QAM_demodulator(){
            // create logger
            logger = spdlog::get("file_logger");

            if(!logger){
                logger = spdlog::basic_logger_mt("file_logger", "../logs.txt");
            }

            QPSK_constellation = generate_constellation(4);
            QAM16_constellation = generate_constellation(16);
            QAM64_constellation = generate_constellation(64);
        }

        // Demodulate symbols to bits. M - count of point in constellation (4, 16, 64)
        std::vector<int8_t> QAM_demodulation(const int& M, const std::vector<sample>& symbols);

    private:
        std::shared_ptr<spdlog::logger> logger;
        std::vector<sample> QPSK_constellation;
        std::vector<sample> QAM16_constellation;
        std::vector<sample> QAM64_constellation;

};