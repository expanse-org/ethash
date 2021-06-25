// frkhash: C/C++ implementation of Frankohash, the Expanse Proof of Work algorithm.
// Copyright 2021-Present Christopher Franko.
// Licensed under the Apache License, Version 2.0.

/// @file
/// Contains declarations of internal frkhash functions to allow them to be
/// unit-tested.

#pragma once

#include <frkhash/frkhash.hpp>

#include "endianness.hpp"

#include <memory>
#include <vector>

namespace frkhash
{
inline bool is_less_or_equal(const hash256& a, const hash256& b) noexcept
{
    for (size_t i = 0; i < (sizeof(a) / sizeof(a.word64s[0])); ++i)
    {
        if (be::uint64(a.word64s[i]) > be::uint64(b.word64s[i]))
            return false;
        if (be::uint64(a.word64s[i]) < be::uint64(b.word64s[i]))
            return true;
    }
    return true;
}

inline bool is_equal(const hash256& a, const hash256& b) noexcept
{
    return std::memcmp(a.bytes, b.bytes, sizeof(a)) == 0;
}

namespace generic
{
using hash_fn_512 = hash512 (*)(const uint8_t* data, size_t size);
}  // namespace generic

}  // namespace frkhash
