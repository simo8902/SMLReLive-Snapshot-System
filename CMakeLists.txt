cmake_minimum_required(VERSION 3.27)
project(SMLRRPro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SMLRRPro SHARED arena.cpp arena.h)

if (MSVC)
    target_compile_options(SMLRRPro PRIVATE /O2 /DNDEBUG /GL /arch:AVX2 /EHs- /EHc- /GR-)
    target_link_options(SMLRRPro PRIVATE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO)
else()
    target_compile_options(SMLRRPro PRIVATE -O3 -DNDEBUG -mavx2 -mfma -fno-exceptions -fno-rtti)
    target_link_options(SMLRRPro PRIVATE -s)
endif()
