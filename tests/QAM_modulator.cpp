#include "../include/QAM_modulator.hpp"

struct test_unit {
    std::vector<int8_t> bits;
    std::complex<float> symbols;
};

// ==================================================== TEST SETS ========================================================================

std::vector<test_unit> qpsk_set = {
    {{0,0}, { 1.0f/std::sqrt(2.0f),  1.0f/std::sqrt(2.0f)}},
    {{0,1}, { 1.0f/std::sqrt(2.0f), -1.0f/std::sqrt(2.0f)}},
    {{1,0}, {-1.0f/std::sqrt(2.0f),  1.0f/std::sqrt(2.0f)}},
    {{1,1}, {-1.0f/std::sqrt(2.0f), -1.0f/std::sqrt(2.0f)}}
};


std::vector<test_unit> qam16_set = {
    {{0,0,0,0}, { 1.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{0,0,0,1}, { 1.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{0,0,1,0}, { 3.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{0,0,1,1}, { 3.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},

    {{0,1,0,0}, { 1.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{0,1,0,1}, { 1.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{0,1,1,0}, { 3.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{0,1,1,1}, { 3.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},

    {{1,0,0,0}, {-1.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{1,0,0,1}, {-1.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{1,0,1,0}, {-3.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{1,0,1,1}, {-3.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},

    {{1,1,0,0}, {-1.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{1,1,0,1}, {-1.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{1,1,1,0}, {-3.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{1,1,1,1}, {-3.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
};


std::vector<test_unit> qam64_set = {

    {{0,0,0,0,0,0}, {  3/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{0,0,0,0,0,1}, {  3/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{0,0,0,1,0,0}, {  3/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{0,0,0,1,0,1}, {  3/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{0,0,1,0,0,0}, {  5/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{0,0,1,0,0,1}, {  5/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{0,0,1,1,0,0}, {  5/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{0,0,1,1,0,1}, {  5/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{0,1,0,0,0,0}, {  3/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{0,1,0,0,0,1}, {  3/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{0,1,0,1,0,0}, {  3/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{0,1,0,1,0,1}, {  3/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{0,1,1,0,0,0}, {  5/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{0,1,1,0,0,1}, {  5/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{0,1,1,1,0,0}, {  5/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{0,1,1,1,0,1}, {  5/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{1,0,0,0,0,0}, { -3/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{1,0,0,0,0,1}, { -3/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{1,0,0,1,0,0}, { -3/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{1,0,0,1,0,1}, { -3/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{1,0,1,0,0,0}, { -5/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{1,0,1,0,0,1}, { -5/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{1,0,1,1,0,0}, { -5/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{1,0,1,1,0,1}, { -5/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{1,1,0,0,0,0}, { -3/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{1,1,0,0,0,1}, { -3/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{1,1,0,1,0,0}, { -3/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{1,1,0,1,0,1}, { -3/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{1,1,1,0,0,0}, { -5/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{1,1,1,0,0,1}, { -5/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{1,1,1,1,0,0}, { -5/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{1,1,1,1,0,1}, { -5/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{0,0,0,0,1,0}, {  1/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{0,0,0,0,1,1}, {  1/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{0,0,0,1,1,0}, {  1/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{0,0,0,1,1,1}, {  1/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{0,0,1,0,1,0}, {  7/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{0,0,1,0,1,1}, {  7/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{0,0,1,1,1,0}, {  7/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{0,0,1,1,1,1}, {  7/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{0,1,0,0,1,0}, {  1/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{0,1,0,0,1,1}, {  1/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{0,1,0,1,1,0}, {  1/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{0,1,0,1,1,1}, {  1/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{0,1,1,0,1,0}, {  7/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{0,1,1,0,1,1}, {  7/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{0,1,1,1,1,0}, {  7/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{0,1,1,1,1,1}, {  7/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{1,0,0,0,1,0}, { -1/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{1,0,0,0,1,1}, { -1/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{1,0,0,1,1,0}, { -1/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{1,0,0,1,1,1}, { -1/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{1,0,1,0,1,0}, { -7/std::sqrt(42.0f),   3/std::sqrt(42.0f)}},
    {{1,0,1,0,1,1}, { -7/std::sqrt(42.0f),   1/std::sqrt(42.0f)}},
    {{1,0,1,1,1,0}, { -7/std::sqrt(42.0f),   5/std::sqrt(42.0f)}},
    {{1,0,1,1,1,1}, { -7/std::sqrt(42.0f),   7/std::sqrt(42.0f)}},

    {{1,1,0,0,1,0}, { -1/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{1,1,0,0,1,1}, { -1/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{1,1,0,1,1,0}, { -1/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{1,1,0,1,1,1}, { -1/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

    {{1,1,1,0,1,0}, { -7/std::sqrt(42.0f),  -3/std::sqrt(42.0f)}},
    {{1,1,1,0,1,1}, { -7/std::sqrt(42.0f),  -1/std::sqrt(42.0f)}},
    {{1,1,1,1,1,0}, { -7/std::sqrt(42.0f),  -5/std::sqrt(42.0f)}},
    {{1,1,1,1,1,1}, { -7/std::sqrt(42.0f),  -7/std::sqrt(42.0f)}},

};


// ============================================================ QPSK TEST =============================================================

void QPKS_TEST(){

    // create modulator
    const int mod_order = 4;
    QAM_modulator modulator;

    sample expected_result;
    std::vector<sample> result;

    int errors = 0;

    // ====================================== POSITIVE CASE ===========================================
    for(const test_unit& el : qpsk_set){
        // user function result
        result = modulator.QAM_modulation(mod_order, el.bits);

        // if function return vector with invalid size
        if(result.size() != 1){
            spdlog::error("[QPSK_TEST]: Invalid size of return symbols!\n\n");
            ++errors;
        }

        expected_result = el.symbols;

        // compare user function result and expected result
        if(result[0] != expected_result){
            spdlog::error("[QPSK_TEST]: Result value non-equal expected value!");
            std::cout << "Result: " << result[0] << "\t" << "Expected: " << expected_result << "\n\n\n";
            ++errors;
        }
    }

    if(errors != 0){
        std::cout << "=========================== QPSK_TEST FAILED! ======================================\n";
    }
    else{
        std::cout << "=========================== QPSK_TEST PASS! ======================================\n";
    }

    // ======================================= NEGATIVE CASE ===========================================
    std::vector<int8_t> invalid_size_data = {0,0,0,0,0};
    std::vector<int8_t> invalid_data = {2,-1};

    // if invalid size
    result = modulator.QAM_modulation(mod_order, invalid_size_data);
    if(!result.empty()){
        spdlog::error("[QPSK_TEST]: Function should return empty vector if input bits size is invalid!");
        ++errors;
    }   

    // if invalid data
    result = modulator.QAM_modulation(mod_order, invalid_data);
    if(!result.empty()){
        spdlog::error("[QPSK_TEST]: Function should return empty vector if input bits have invalid values!");
        ++errors;
    }
    
    
    // conclusion
    if(errors != 0){
        std::cout << "=========================== QPSK_TEST FAILED! ======================================\n";
    }
    else{
        std::cout << "=========================== QPSK_TEST PASS! ======================================\n";
    }
}

void QAM16_TEST(){

    // create modulator
    const int mod_order = 16;
    QAM_modulator modulator;

    sample expected_result;
    std::vector<sample> result;

    int errors = 0;

    // ====================================== POSITIVE CASE ===========================================
    for(const test_unit& el : qam16_set){
        // user function result
        result = modulator.QAM_modulation(mod_order, el.bits);

        // if function return vector with invalid size
        if(result.size() != 1){
            spdlog::error("[QAM16_TEST]: Invalid size of return symbols!\n\n");
            ++errors;
            continue;
        }

        expected_result = el.symbols;

        // compare user function result and expected result
        double eps = 1e-6;
        if(std::fabs(result[0].real() - expected_result.real()) > eps || std::fabs(result[0].imag() - expected_result.imag()) > eps){
            spdlog::error("[QAM16_TEST]: Result value non-equal expected value!");
            std::cout << "Result: " << result[0] << "\t" << "Expected: " << expected_result << "\n\n\n";
            ++errors;
        }
    }

    // ======================================= NEGATIVE CASE ===========================================
    std::vector<int8_t> invalid_size_data = {0,0,0,0,0};
    std::vector<int8_t> invalid_data = {2,-1,1,2};

    // if invalid size
    result = modulator.QAM_modulation(mod_order, invalid_size_data);
    if(!result.empty()){
        spdlog::error("[QAM16_TEST]: Function should return empty vector if input bits size is invalid!");
        ++errors;
    }   

    // if invalid data
    result = modulator.QAM_modulation(mod_order, invalid_data);
    if(!result.empty()){
        spdlog::error("[QAM16_TEST]: Function should return empty vector if input bits have invalid values!");
        ++errors;
    }   

    // conclusion
    if(errors != 0){
        std::cout << "=========================== QAM16_TEST FAILED! ======================================\n";
    }
    else{
        std::cout << "=========================== QAM16_TEST PASS! ======================================\n";
    }
}

void QAM64_TEST(){

    // create modulator
    const int mod_order = 64;
    QAM_modulator modulator;

    sample expected_result;
    std::vector<sample> result;

    int errors = 0;

    // ====================================== POSITIVE CASE ===========================================
    for(const test_unit& el : qam64_set){
        // user function result
        result = modulator.QAM_modulation(mod_order, el.bits);

        // if function return vector with invalid size
        if(result.size() != 1){
            spdlog::error("[QAM64_TEST]: Invalid size of return symbols!\n\n");
            ++errors;
        }

        expected_result = el.symbols;

        // compare user function result and expected result
        if(result[0] != expected_result){
            spdlog::error("[QAM64_TEST]: Result value non-equal expected value!");
            std::cout << "Result: " << result[0] << "\t" << "Expected: " << expected_result << "\n\n\n";
            ++errors;
        }
    }

    // ======================================= NEGATIVE CASE ===========================================
    std::vector<int8_t> invalid_size_data = {0,0,0,0,0};
    std::vector<int8_t> invalid_data = {2,-1,1,2,4,0};

    // if invalid size
    result = modulator.QAM_modulation(mod_order, invalid_size_data);
    if(!result.empty()){
        spdlog::error("[QAM64_TEST]: Function should return empty vector if input bits size is invalid!");
        ++errors;
    }   

    // if invalid data
    result = modulator.QAM_modulation(mod_order, invalid_data);
    if(!result.empty()){
        spdlog::error("[QAM64_TEST]: Function should return empty vector if input bits have invalid values!");
        ++errors;
    }   
    
    // conclusion
    if(errors != 0){
        std::cout << "=========================== QAM64_TEST FAILED! ======================================\n";
    }
    else{
        std::cout << "=========================== QAM64_TEST PASS! ======================================\n";
    }
}

int main(){
    QPKS_TEST();
    QAM16_TEST();
    QAM64_TEST();

    return 0;
}