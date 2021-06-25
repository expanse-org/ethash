// frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include <frkhash/frkhash.hpp>
#include <frkhash/version.h>

int main()
{
    static_assert(sizeof(frkhash::version) >= 6, "incorrect frkhash::version");

    uint8_t seed_bytes[32] = {0};
    frkhash::hash256 seed = frkhash::hash256_from_bytes(seed_bytes);
    return frkhash::find_epoch_number(seed);
}
