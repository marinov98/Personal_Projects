cmake_minimum_required(VERSION 3.12)
project(statistical_calculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SRCS "*.cpp")
file(GLOB HDRS "*.hpp")

add_executable(statistical_calculator ${SRCS} ${HDRS})
