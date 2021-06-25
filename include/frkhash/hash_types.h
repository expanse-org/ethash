/* frkhash: C/C++ implementation of Frankohash, the Expanse Proof of Work algorithm.
 * Copyright 2021-Present Christopher Franko.
 * Licensed under the Apache License, Version 2.0.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

union frkhash_hash256
{
    uint64_t word64s[4];
    uint32_t word32s[8];
    uint8_t bytes[32];
    char str[32];
};

union frkhash_hash512
{
    uint64_t word64s[8];
    uint32_t word32s[16];
    uint8_t bytes[64];
    char str[64];
};

union frkhash_hash1024
{
    union frkhash_hash512 hash512s[2];
    uint64_t word64s[16];
    uint32_t word32s[32];
    uint8_t bytes[128];
    char str[128];
};

union frkhash_hash2048
{
    union frkhash_hash512 hash512s[4];
    uint64_t word64s[32];
    uint32_t word32s[64];
    uint8_t bytes[256];
    char str[256];
};

#ifdef __cplusplus
}
#endif
