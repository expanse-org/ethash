// frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
// Copyright 2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include <frkhash/version.h>

#include <gtest/gtest.h>

TEST(libfrkhash, version)
{
    static_assert(frkhash::version[0] != 0, "incorrect frkhash::version");

    EXPECT_EQ(FRKHASH_VERSION, TEST_PROJECT_VERSION);
    EXPECT_EQ(frkhash::version, TEST_PROJECT_VERSION);
}
