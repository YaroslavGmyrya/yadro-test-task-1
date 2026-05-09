cmake_minimum_required(VERSION 4.2.3)
project(main LANGUAGES CXX)

# find spdlog
find_package(spdlog REQUIRED)

# set source file
set(SRC 
    src/main.cpp
    src/QAM_modulator.cpp
)

# create executable file
add_executable(main ${SRC})

#link lib
target_link_libraries(main PRIVATE spdlog::spdlog)
