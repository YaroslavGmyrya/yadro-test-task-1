#include <spdlog/spdlog.h>


int GENERATE_BITS_TEST();
int DEC_TO_BIN_TEST();
int BIN_TO_DEC_TEST();
int QAM_MODEM_TEST();
int QAM_CONSTELLATION_TEST();
int CHANNEL_TEST();

int main(){
    if(GENERATE_BITS_TEST()){
        spdlog::error("#1 GENERATE_BITS_TEST failed!\n\n");
    }
    else{
        spdlog::info("#1 GENERATE_BITS_TEST passed!\n\n");
    }

    if(DEC_TO_BIN_TEST()){
        spdlog::error("#2 DEC_TO_BIN_TEST failed!\n\n");
    }
    else{
        spdlog::info("#2 DEC_TO_BIN_TEST passed!\n\n");
    }

    if(BIN_TO_DEC_TEST()){
        spdlog::error("#3 BIN_TO_DEC_TEST failed!\n\n");
    }
    else{
        spdlog::info("#3 BIN_TO_DEC_TEST passed!\n\n");
    }

    if(QAM_CONSTELLATION_TEST()){
        spdlog::error("#4 QAM_CONSTELLATION_TEST failed!\n\n");
    }
    else{
        spdlog::info("#4 QAM_CONSTELLATION_TEST passed!\n\n");
    }

    if(CHANNEL_TEST()){
        spdlog::error("#5 CHANNEL_TEST failed!\n\n");
    }
    else{
        spdlog::info("#5 CHANNEL_TEST passed!\n\n");
    }

    if(QAM_MODEM_TEST()){
        spdlog::error("#6 QAM_MODEM_TEST failed! Check logs!\n\n");
    }
    else{
        spdlog::info("#6 QAM_MODEM_TEST passed!\n\n");
    }

    return 0;
}