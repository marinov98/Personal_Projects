cmake_minimum_required(VERSION 3.12)
project(statistical_calculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SRCS "src/*.cpp")
file(GLOB HDRS "src/*.hpp")

add_executable(statistical_calculator ${SRCS} ${HDRS})
