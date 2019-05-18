# REQUIREMENTS
cmake_minimum_required(VERSION 3.12)
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
	
# PROJECT NAME
project(statistical_calculator)

# REQUIRES C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

# find_package(doctest CONFIG REQUIRED)

file(GLOB SRCS "src/*.cpp")
file(GLOB HDRS "src/*.hpp")

add_executable(statistical_calculator ${SRCS} ${HDRS})

# target_link_libraries(statistical_calculator PRIVATE doctest::doctest)
