# Frkhash

[![readme style standard](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

> C/C++ implementation of Frkhash – the new Expanse Proof of Work algorithm


## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Test vectors](#test-vectors)
- [Optimizations](#optimizations)
- [Maintainer](#maintainer)
- [License](#license)


## Install

Build from source using CMake.

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

See [frkhash.hpp] for list of exported function and documentation.


## Test vectors

- [ProgPoW test vectors](test/unittests/progpow_test_vectors.hpp)


## Optimizations

This section describes the optimizations, modification and tweaks applied
in this library in relation to [Frkhash reference implementation].

The library contains a set of micro-benchmarks. Build and run `bench` tool.


## Maintainer

Christopher Franko [@chrisfranko]

## License

Licensed under the [Apache License, Version 2.0].


[@chrisfrano]: https://github.com/chrisfranko
[Apache License, Version 2.0]: LICENSE
[frkhash.hpp]: include/frkhash/frkhash.hpp
[Frkhash reference implementation]: https://github.com/ethereum/wiki/wiki/Frkhash
