# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

add_subdirectory(keccak)

if(FRKHASH_BUILD_FRKHASH)
    add_subdirectory(frkhash)
endif()

# if(FRKHASH_BUILD_GLOBAL_CONTEXT)
#     add_subdirectory(global_context)
# endif()

get_filename_component(FRKHASH_PRIVATE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
set(FRKHASH_PRIVATE_INCLUDE_DIR ${FRKHASH_PRIVATE_INCLUDE_DIR} PARENT_SCOPE)
