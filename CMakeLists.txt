cmake_minimum_required(VERSION 4.2.3)

project(main LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

find_package(spdlog REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Development NumPy)

set(SRC
    src/QAM_modem.cpp
    src/channel.cpp
    src/sub_funcs.cpp
    src/simulation.cpp
)

set(TEST
    tests/main_test.cpp
    tests/sub_funcs_test.cpp
    tests/QAM_modem_test.cpp
    tests/channel_test.cpp
)

add_executable(main ${SRC} src/main.cpp)

add_executable(tests ${TEST} ${SRC})

target_include_directories(main PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(main PRIVATE spdlog::spdlog Python3::Python Python3::NumPy)

target_link_libraries(tests PRIVATE spdlog::spdlog Python3::Python Python3::NumPy)