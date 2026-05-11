cmake_minimum_required(VERSION 4.2.3)
project(main LANGUAGES CXX)

# find spdlog
find_package(spdlog REQUIRED)

# set source files
set(SRC 
    src/QAM_modem.cpp
    src/channel.cpp
    src/sub_funcs.cpp
)

# set tests files
set(TEST 
    tests/main_test.cpp
    tests/sub_funcs_test.cpp
    tests/QAM_modem_test.cpp
    tests/channel_test.cpp
)

# create executable file
add_executable(main ${SRC} src/main.cpp)
add_executable(tests ${TEST} ${SRC})

#link lib
target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(tests PRIVATE spdlog::spdlog)
