cmake_minimum_required(VERSION 3.9)
project(MarinSideProject CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS False)

# include(third-party/cmake-utils/include/warnings.cmake)

# add_library(doctest::doctest INTERFACE IMPORTED)
# set_target_properties(doctest::doctest PROPERTIES
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/third-party/doctest-in-repo/doctest"
#     INTERFACE_COMPILE_FEATURES cxx_std_14
# )

add_library(msvc::unicode INTERFACE IMPORTED)
if (MSVC)
    set_target_properties(msvc::unicode PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "UNICODE;_UNICODE"
    )
endif()

add_executable(main basics.cpp main.cpp basics.h)
