cmake_minimum_required(VERSION 4.2.3)
project(main LANGUAGES CXX)

# find spdlog
find_package(spdlog REQUIRED)

# set source file
set(SRC 
    src/QAM_modem.cpp
    src/channel.cpp
    src/sub_funcs.cpp
)

set(TEST 
    tests/main.cpp
    tests/sub_funcs.cpp
    tests/QAM_modem.cpp
)

# create executable file
add_executable(main ${SRC} src/main.cpp)
add_executable(tests ${TEST} ${SRC})

#link lib
target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(tests PRIVATE spdlog::spdlog)
