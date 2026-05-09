#include "../include/QAM_modulator.hpp"

struct test_unit {
    std::vector<int8_t> bits;
    std::complex<float> symbols;
};

// ==================================================== TEST SETS ========================================================================

std::vector<test_unit> qpsk_tests = {
    {{0,0}, { 1.0f/std::sqrt(2.0f),  1.0f/std::sqrt(2.0f)}},
    {{0,1}, { 1.0f/std::sqrt(2.0f), -1.0f/std::sqrt(2.0f)}},
    {{1,0}, {-1.0f/std::sqrt(2.0f),  1.0f/std::sqrt(2.0f)}},
    {{1,1}, {-1.0f/std::sqrt(2.0f), -1.0f/std::sqrt(2.0f)}}
};

std::vector<test_unit> qam16_tests = {
    {{0,0,0,0}, { -3.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{0,0,0,1}, { -1.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{0,0,1,0}, {  3.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{0,0,1,1}, {  1.0f/std::sqrt(10.0f), -3.0f/std::sqrt(10.0f)}},
    {{0,1,0,0}, { -3.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{0,1,0,1}, { -1.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{0,1,1,0}, {  3.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{0,1,1,1}, {  1.0f/std::sqrt(10.0f), -1.0f/std::sqrt(10.0f)}},
    {{1,0,0,0}, { -3.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{1,0,0,1}, { -1.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{1,0,1,0}, {  3.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{1,0,1,1}, {  1.0f/std::sqrt(10.0f),  3.0f/std::sqrt(10.0f)}},
    {{1,1,0,0}, { -3.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{1,1,0,1}, { -1.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{1,1,1,0}, {  3.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}},
    {{1,1,1,1}, {  1.0f/std::sqrt(10.0f),  1.0f/std::sqrt(10.0f)}}
};

std::vector<test_unit> qam64_tests = {
    {{0,0,0,0,0,0}, {-7/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{0,0,0,0,0,1}, {-7/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{0,0,0,0,1,0}, {-7/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{0,0,0,0,1,1}, {-7/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{0,0,0,1,0,0}, {-7/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{0,0,0,1,0,1}, {-7/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{0,0,0,1,1,0}, {-7/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{0,0,0,1,1,1}, {-7/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{0,0,1,0,0,0}, {-5/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{0,0,1,0,0,1}, {-5/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{0,0,1,0,1,0}, {-5/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{0,0,1,0,1,1}, {-5/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{0,0,1,1,0,0}, {-5/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{0,0,1,1,0,1}, {-5/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{0,0,1,1,1,0}, {-5/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{0,0,1,1,1,1}, {-5/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{0,1,0,0,0,0}, {-1/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{0,1,0,0,0,1}, {-1/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{0,1,0,0,1,0}, {-1/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{0,1,0,0,1,1}, {-1/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{0,1,0,1,0,0}, {-1/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{0,1,0,1,0,1}, {-1/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{0,1,0,1,1,0}, {-1/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{0,1,0,1,1,1}, {-1/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{0,1,1,0,0,0}, {-3/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{0,1,1,0,0,1}, {-3/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{0,1,1,0,1,0}, {-3/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{0,1,1,0,1,1}, {-3/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{0,1,1,1,0,0}, {-3/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{0,1,1,1,0,1}, {-3/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{0,1,1,1,1,0}, {-3/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{0,1,1,1,1,1}, {-3/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{1,0,0,0,0,0}, { 7/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{1,0,0,0,0,1}, { 7/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{1,0,0,0,1,0}, { 7/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{1,0,0,0,1,1}, { 7/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{1,0,0,1,0,0}, { 7/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{1,0,0,1,0,1}, { 7/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{1,0,0,1,1,0}, { 7/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{1,0,0,1,1,1}, { 7/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{1,0,1,0,0,0}, { 5/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{1,0,1,0,0,1}, { 5/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{1,0,1,0,1,0}, { 5/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{1,0,1,0,1,1}, { 5/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{1,0,1,1,0,0}, { 5/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{1,0,1,1,0,1}, { 5/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{1,0,1,1,1,0}, { 5/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{1,0,1,1,1,1}, { 5/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{1,1,0,0,0,0}, { 1/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{1,1,0,0,0,1}, { 1/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{1,1,0,0,1,0}, { 1/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{1,1,0,0,1,1}, { 1/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{1,1,0,1,0,0}, { 1/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{1,1,0,1,0,1}, { 1/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{1,1,0,1,1,0}, { 1/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{1,1,0,1,1,1}, { 1/std::sqrt(42.0f),  3/std::sqrt(42.0f)}},

    {{1,1,1,0,0,0}, { 3/std::sqrt(42.0f), -7/std::sqrt(42.0f)}},
    {{1,1,1,0,0,1}, { 3/std::sqrt(42.0f), -5/std::sqrt(42.0f)}},
    {{1,1,1,0,1,0}, { 3/std::sqrt(42.0f), -1/std::sqrt(42.0f)}},
    {{1,1,1,0,1,1}, { 3/std::sqrt(42.0f), -3/std::sqrt(42.0f)}},
    {{1,1,1,1,0,0}, { 3/std::sqrt(42.0f),  7/std::sqrt(42.0f)}},
    {{1,1,1,1,0,1}, { 3/std::sqrt(42.0f),  5/std::sqrt(42.0f)}},
    {{1,1,1,1,1,0}, { 3/std::sqrt(42.0f),  1/std::sqrt(42.0f)}},
    {{1,1,1,1,1,1}, { 3/std::sqrt(42.0f),  3/std::sqrt(42.0f)}}
};

