/* frkhash: C/C++ implementation of Frankohash, the Expanse Proof of Work algorithm.
 * Copyright 2021-Present Christopher Franko.
 * Licensed under the Apache License, Version 2.0.
 */

#pragma once

#include <frkhash/frkhash.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Finds the largest prime number not greater than the provided upper bound.
 *
 * @param upper_bound  The upper bound. SHOULD be greater than 1.
 * @return  The largest prime number `p` such `p <= upper_bound`.
 *          In case `upper_bound <= 1`, returns 0.
 */
int frkhash_find_largest_prime(int upper_bound) NOEXCEPT;

#ifdef __cplusplus
}
#endif
