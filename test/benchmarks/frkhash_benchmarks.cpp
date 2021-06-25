// frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include "../unittests/helpers.hpp"

#include <benchmark/benchmark.h>
#include <frkhash/frkhash-internal.hpp>
#include <frkhash/keccak.hpp>
#include <frkhash/primes.h>


static void frkhash_hash(benchmark::State& state)
{
    uint64_t nonce = 1;

    for (auto _ : state)
        frkhash::hash({}, nonce++);
}
BENCHMARK(frkhash_hash)->Unit(benchmark::kMicrosecond)->Arg(0)->Arg(10);


static void verify(benchmark::State& state)
{
    const frkhash::hash256 header_hash =
        to_hash256("bc544c2baba832600013bd5d1983f592e9557d04b0fb5ef7a100434a5fc8d52a");
    const frkhash::hash256 mix_hash =
        to_hash256("94cd4e844619ee20989578276a0a9046877d569d37ba076bf2e8e34f76189dea");
    const uint64_t nonce = 0x4617a20003ba3f25;
    const frkhash::hash256 boundry =
        to_hash256("0000000000001a5c000000000000000000000000000000000000000000000000");

    for (auto _ : state)
        frkhash::verify(header_hash, mix_hash, nonce, boundry);
}
BENCHMARK(verify);


static void verify_mt(benchmark::State& state)
{
    const frkhash::hash256 header_hash =
        to_hash256("bc544c2baba832600013bd5d1983f592e9557d04b0fb5ef7a100434a5fc8d52a");
    const frkhash::hash256 mix_hash =
        to_hash256("94cd4e844619ee20989578276a0a9046877d569d37ba076bf2e8e34f76189dea");
    const uint64_t nonce = 0x4617a20003ba3f25;
    const frkhash::hash256 boundry =
        to_hash256("0000000000001a5c000000000000000000000000000000000000000000000000");

    for (auto _ : state)
        frkhash::verify(header_hash, mix_hash, nonce, boundry);
}
BENCHMARK(verify_mt)->Threads(1)->Threads(2)->Threads(4)->Threads(8);


static void verify_managed(benchmark::State& state)
{
    const frkhash::hash256 header_hash =
        to_hash256("bc544c2baba832600013bd5d1983f592e9557d04b0fb5ef7a100434a5fc8d52a");
    const frkhash::hash256 mix_hash =
        to_hash256("94cd4e844619ee20989578276a0a9046877d569d37ba076bf2e8e34f76189dea");
    const uint64_t nonce = 0x4617a20003ba3f25;
    const frkhash::hash256 boundry =
        to_hash256("0000000000001a5c000000000000000000000000000000000000000000000000");

    for (auto _ : state)
    {
        frkhash::verify(header_hash, mix_hash, nonce, boundry);
    }
}
BENCHMARK(verify_managed)->Threads(1)->Threads(2)->Threads(4)->Threads(8);


BENCHMARK_MAIN();
