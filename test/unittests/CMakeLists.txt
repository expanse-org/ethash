# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2018-2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(
    frkhash-test
    helpers.hpp
    test_bit_manipulation.cpp
    test_cases.hpp
    test_frkhash.cpp
    test_keccak.cpp
    test_kiss.cpp
    test_primes.cpp
    test_version.cpp
)

set_source_files_properties(test_version.cpp PROPERTIES COMPILE_DEFINITIONS TEST_PROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(frkhash-test PRIVATE frkhash GTest::gtest_main)
target_include_directories(frkhash-test PRIVATE ${FRKHASH_PRIVATE_INCLUDE_DIR})
set_target_properties(frkhash-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ..)

if(SANITIZE AND CMAKE_SYSTEM_NAME STREQUAL Linux AND CMAKE_CXX_FLAGS MATCHES -m32)
    # Workaround for linking with phread when building for 32-bit and with sanitizer.
    target_link_libraries(frkhash-test PRIVATE pthread)
endif()
