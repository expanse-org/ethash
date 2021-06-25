# Copyright 2018-2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

cmake_minimum_required(VERSION 3.5)

project(frkhash-cmake-config-test)

find_package(frkhash CONFIG REQUIRED)

add_executable(frkhash-cmake-config-test cmake_config_test.cpp)
target_link_libraries(frkhash-cmake-config-test frkhash::frkhash)
set_target_properties(frkhash-cmake-config-test PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS OFF)
