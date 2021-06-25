# frkhash: C/C++ implementation of Frankohash, the Expanse Proof of Work algorithm.
# Copyright 2021-Present Christopher Franko.
# Licensed under the Apache License, Version 2.0.

add_library(frkhash)
add_library(frkhash::frkhash ALIAS frkhash)
target_link_libraries(frkhash PRIVATE frkhash::keccak)
target_include_directories(frkhash PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_sources(frkhash PRIVATE
    bit_manipulation.h
    builtins.h
    endianness.hpp
    ${PROJECT_SOURCE_DIR}/include/frkhash/frkhash.h
    ${PROJECT_SOURCE_DIR}/include/frkhash/frkhash.hpp
    frkhash.cpp
    ${PROJECT_SOURCE_DIR}/include/frkhash/hash_types.h
    managed.cpp
    kiss99.hpp
    primes.h
    primes.c
)


if(CABLE_COMPILER_GNULIKE AND NOT SANITIZE MATCHES undefined)
    target_compile_options(frkhash PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
endif()
