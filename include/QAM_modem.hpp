#pragma once

#include <iostream>
#include <complex>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#define QAM16_THRESHOLD (2 / sqrtf(10))

#define QAM64_THRESHOLD_1 (2 / sqrtf(42))
#define QAM64_THRESHOLD_2 (4 / sqrtf(42))
#define QAM64_THRESHOLD_3 (6 / sqrtf(42))

using sample = std::complex<float>;

enum mod_type {
    QPSK = 4,
    QAM16 = 16,
    QAM64 = 64
};

inline std::vector<mod_type> allowed_modulations = {QPSK, QAM16, QAM64};

class QAM_base{
    public:
        QAM_base(const std::string& logger_name, const std::string log_filename){
        
        // create logger
        logger = spdlog::get(logger_name);

        if(!logger){
            logger = spdlog::basic_logger_mt(logger_name, "../logs/" + log_filename);
        }

        // generate constellations
        for(const mod_type& order : allowed_modulations)
            constellations[(int)order] = generate_constellation(order);
    }

    std::vector<sample> generate_constellation(const mod_type& M);

    protected:
        std::unordered_map<int, std::vector<sample>> constellations;

        std::shared_ptr<spdlog::logger> logger;

};

class QAM_modulator : public QAM_base {
    public:
        QAM_modulator() : QAM_base("QAM_modulator_logger", "QAM_modulator_logs.txt"){}

        // Modulate bits to symbols. M - count of point in constellation (4, 16, 64)
        std::vector<sample> QAM_modulation(const std::vector<int8_t>& bits, const mod_type& M);
};

class QAM_demodulator : public QAM_base {    
    public:
        QAM_demodulator() : QAM_base("QAM_demodulator_logger", "QAM_demodulator_logs.txt"){}

        // Demodulate symbols to bits. M - count of point in constellation (4, 16, 64)
        std::vector<int8_t> QAM_soft_demodulation(const std::vector<sample>& symbols, const mod_type& M);
        std::vector<int8_t> QAM_hard_demodulation(const std::vector<sample>& symbols, const mod_type& M);

    private:
        std::vector<int8_t> QPSK_hard_demodulation(const std::vector<sample>& symbols);
        std::vector<int8_t> QAM16_hard_demodulation(const std::vector<sample>& symbols);
        std::vector<int8_t> QAM64_hard_demodulation(const std::vector<sample>& symbols);
};