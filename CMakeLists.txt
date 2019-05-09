cmake_minimum_required(VERSION 3.12)
project(statistical_calculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(statistical_calculator
        main.cpp
        basics.cpp basics.hpp
        cInterval.cpp cInterval.hpp
        correlation.cpp correlation.hpp
        hypTest.cpp hypTest.hpp)
