// frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.
// These test are going to need cleaned up with valid data hashed

#pragma GCC diagnostic ignored "-Wpedantic"
#pragma clang diagnostic ignored "-Wpedantic"
#pragma warning(disable : 4127)

#include <frkhash/endianness.hpp>
#include <frkhash/frkhash-internal.hpp>
#include <frkhash/frkhash.hpp>
#include <frkhash/keccak.hpp>

#include "helpers.hpp"
#include "test_cases.hpp"

#include <gtest/gtest.h>

#include <array>
#include <future>

using namespace frkhash;

namespace
{
hash512 copy(const hash512& h) noexcept
{
    return h;
}
}

TEST(frkhash, revision)
{
    static_assert(frkhash::revision[0] == '2', "");
    static_assert(frkhash::revision[1] == '3', "");
    EXPECT_EQ(frkhash::revision, "23");
    EXPECT_EQ(frkhash::revision, (std::string{"23"}));
}

TEST(hash, hash256_from_bytes)
{
    const uint8_t bytes[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    auto h = hash256_from_bytes(bytes);
    EXPECT_EQ(to_hex(h), "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
}

TEST(hash, hash256_from_bytes64)
{
    const uint8_t bytes[64] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    auto h = hash256_from_bytes64(bytes);
    EXPECT_EQ(to_hex(h), "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
}

TEST(hash, hash512_init)
{
    hash512 hash = {};
    for (auto w : hash.word64s)
        EXPECT_EQ(w, 0);

    hash512 hash2 = copy({});
    for (auto w : hash2.word64s)
        EXPECT_EQ(w, 0);
}

TEST(hash, hash1024_init)
{
    hash1024 hash = {};
    for (auto w : hash.word64s)
        EXPECT_EQ(w, 0);
}

TEST(frkhash, verify_hash)
{

    for (const auto& t : hash_test_cases)
    {
        const uint64_t nonce = std::stoull(t.nonce_hex, nullptr, 16);
        const hash256 header_hash = to_hash256(t.header_hash_hex);

        result r = hash(header_hash, nonce);
        EXPECT_EQ(to_hex(r.final_hash), t.final_hash_hex);
        EXPECT_EQ(to_hex(r.mix_hash), t.mix_hash_hex);
    }
}

TEST(frkhash, verify_final_hash_only)
{
    const hash256 header_hash = {};
    const hash256 mix_hash = {};
    uint64_t nonce = 3221208;
    const hash256 boundary =
        to_hash256("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

    EXPECT_TRUE(verify_final_hash(header_hash, nonce, boundary));
    EXPECT_FALSE(verify(header_hash, mix_hash, nonce, boundary));
}

TEST(frkhash, verify_boundary)
{
    hash256 example_header_hash =
        to_hash256("e74e5e8688d3c6f17885fa5e64eb6718046b57895a2a24c593593070ab71f5fd");
    uint64_t nonce = 6666;
    auto r = hash(example_header_hash, nonce);
    hash256 boundary_eq =
        to_hash256("13c5a668bba6b86ed16098113d9d6a7a5cac1802e9c8f2d57c932d8818375eb7");

    hash256 boundary_gt = boundary_eq;
    ++boundary_gt.bytes[31];
    auto boundary_gt_hex = "13c5a668bba6b86ed16098113d9d6a7a5cac1802e9c8f2d57c932d8818375eb8";
    EXPECT_EQ(to_hex(boundary_gt), boundary_gt_hex);

    hash256 boundary_lt = boundary_eq;
    --boundary_lt.bytes[31];
    auto boundary_lt_hex = "13c5a668bba6b86ed16098113d9d6a7a5cac1802e9c8f2d57c932d8818375eb6";
    EXPECT_EQ(to_hex(boundary_lt), boundary_lt_hex);

    EXPECT_EQ(r.final_hash, boundary_eq);
    EXPECT_EQ(to_hex(r.final_hash), to_hex(boundary_eq));

    EXPECT_TRUE(verify(example_header_hash, r.mix_hash, nonce, boundary_eq));
    EXPECT_TRUE(verify(example_header_hash, r.mix_hash, nonce, boundary_gt));
    EXPECT_FALSE(verify(example_header_hash, r.mix_hash, nonce, boundary_lt));
}

static constexpr bool arch64bit = sizeof(void*) == 8;

#endif

namespace
{
struct is_less_or_equal_test_case
{
    const char* a_hex;
    const char* b_hex;
    bool excected_result;
};

is_less_or_equal_test_case is_less_or_equal_test_cases[] = {
    {"0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000000", true},
    {"0000000000000000000000000000000000000000000000000000000000000001",
        "0000000000000000000000000000000000000000000000000000000000000000", false},
    {"0000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000001", true},
    {"0000000000000000000000000000000000000000000000000000000000000001",
        "0000000000000000000000000000000000000000000000000000000000000100", true},
    {"1000000000000000000000000000000000000000000000000000000000000000",
        "0000000000000000000000000000000000000000000000000000000000000001", false},
    {"1000000000000000000000000000000000000000000000000000000000000000",
        "0010000000000000000000000000000000000000000000000000000000000000", false},
    {"0000000000000000000000000010000000000000000000000000000000000000",
        "0000000000000000000000000001000000000000000000000000000000000000", false},
    {"0000000000000000000000000010000000000000000000000000000000000000",
        "0000000000000000000000000010000000000000000000000000000000000000", true},
    {"1000000000000000000000000000000000000000000000000000000000000001",
        "1000000000000000000000000000000000000000000000000000000000000002", true},
    {"2000000000000000000000000000000000000000000000000000000000000001",
        "1000000000000000000000000000000000000000000000000000000000000002", false},
    {"1000000000000000000000000000000000000000000000000000000000000000",
        "2000000000000000000000000000000000000000000000000000000000000000", true},
    {"1000000000000000200000000000000000000000000000000000000000000000",
        "2000000000000000100000000000000000000000000000000000000000000000", true},
    {"aaaaaaaaaaaaaaaa100000000000000000000000000000000000000000000000",
        "aaaaaaaaaaaaaaaa100000000000000000000000000000000000000000000000", true},
    {"aaaaaaaaaaaaaaaa100000000000000000000000000000000000000000000000",
        "aaaaaaaaaaaaaaaa200000000000000000000000000000000000000000000000", true},
    {"aaaaaaaaaaaaaaaa200000000000000000000000000000000000000000000000",
        "aaaaaaaaaaaaaaaa100000000000000000000000000000000000000000000000", false},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa10000000000000000000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa10000000000000000000000000000000", true},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa10000000000000000000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa20000000000000000000000000000000", true},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa20000000000000000000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa10000000000000000000000000000000", false},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1000000000000000", true},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2000000000000000", true},
    {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2000000000000000",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa1000000000000000", false},
};
}  // namespace

TEST(frkhash, is_less_or_equal)
{
    for (const auto& t : is_less_or_equal_test_cases)
    {
        auto a = to_hash256(t.a_hex);
        auto b = to_hash256(t.b_hex);
        EXPECT_EQ(is_less_or_equal(a, b), t.excected_result);
    }
}
