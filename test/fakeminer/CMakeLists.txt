# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2018-2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

find_package(Threads)

add_executable(frkhash-fakeminer fakeminer.cpp)
target_link_libraries(frkhash-fakeminer PRIVATE frkhash Threads::Threads)
set_target_properties(frkhash-fakeminer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
