/* frkhash: C/C++ implementation of Frankohash, the Expanse Proof of Work algorithm.
 * Copyright 2021-Present Christopher Franko.
 * Licensed under the Apache License, Version 2.0.
 */

#pragma once

#include <frkhash/hash_types.h>

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Frankohash algorithm revision implemented as specified in the Frankohash spec
 * https://github.com/ethereum/wiki/wiki/Frankohash.
 */
#define FRKHASH_REVISION "23"

struct frkhash_result
{
    union frkhash_hash256 final_hash;
    union frkhash_hash256 mix_hash;
};

struct frkhash_result frkhash_hash(
    const union frkhash_hash256* header_hash, uint64_t nonce) NOEXCEPT;

bool frkhash_verify(
    const union frkhash_hash256* header_hash, const union frkhash_hash256* mix_hash, uint64_t nonce,
    const union frkhash_hash256* boundary) NOEXCEPT;

bool frkhash_verify_final_hash(
    const union frkhash_hash256* mix_hash, uint64_t nonce,
    const union frkhash_hash256* boundary) NOEXCEPT;

#ifdef __cplusplus
}
#endif
