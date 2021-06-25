# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2018-2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

hunter_add_package(benchmark)
find_package(benchmark CONFIG REQUIRED)

add_executable(frkhash-bench
    frkhash_benchmarks.cpp
    keccak_benchmarks.cpp
    keccak_utils.hpp
    keccak_utils.cpp
    threadsync_benchmarks.cpp
    threadsync_utils.hpp
    threadsync_utils.cpp)
target_link_libraries(frkhash-bench PRIVATE frkhash benchmark::benchmark)
target_include_directories(frkhash-bench PRIVATE ${FRKHASH_PRIVATE_INCLUDE_DIR})
set_target_properties(frkhash-bench PROPERTIES RUNTIME_OUTPUT_DIRECTORY ..)
