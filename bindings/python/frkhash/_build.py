# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

# The CFFI build script for frkhash library.
# It expects the library is installed in the dist/ directory.
# The installation can be performed by
#
#     cmake . -DCMAKE_INSTALL_PREFIX=dist
#     make
#     make install

from cffi import FFI
import sys

ffibuilder = FFI()

stdlib = []
if sys.platform == 'linux':
    stdlib.append('stdc++')

ffibuilder.set_source(
    "_frkhash",
    r"""
    #include <frkhash/keccak.h>
    #include <frkhash/frkhash.h>
     """,
    include_dirs=['include'],
    libraries=['frkhash', 'keccak'] + stdlib,
)

ffibuilder.cdef("""

union frkhash_hash256
{
    ...;
    char str[32];
};

union frkhash_hash512
{
    ...;
    char str[64];
};

struct frkhash_result
{
    union frkhash_hash256 final_hash;
    union frkhash_hash256 mix_hash;
};


union frkhash_hash256 frkhash_keccak256(const uint8_t* data, size_t size);

union frkhash_hash512 frkhash_keccak512(const uint8_t* data, size_t size);

struct frkhash_result frkhash_hash(const union frkhash_hash256* header_hash, uint64_t nonce);

bool frkhash_verify(const union frkhash_hash256* header_hash,
    const union frkhash_hash256* mix_hash, uint64_t nonce,
    const union frkhash_hash256* boundary);

""")

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
