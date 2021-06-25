# frkhash: C/C++ implementation of Frkhash, the Expanse Proof of Work algorithm.
# Copyright 2018-2019 Pawel Bylica.
# Licensed under the Apache License, Version 2.0.

cmake_minimum_required(VERSION 3.13.4)

include(cmake/cable/bootstrap.cmake)

include(CableBuildType)
include(CableCompilerSettings)
include(CableToolchains)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(HunterGate)

include(defaults/HunterCacheServers)

cable_configure_toolchain(DEFAULT cxx11)
cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Release RelWithDebInfo Debug)

if(NOT WIN32)
    # Outside of Windows build only Release packages.
    set(HUNTER_CONFIGURATION_TYPES Release
        CACHE STRING "Build type of the Hunter packages")
endif()

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.224.tar.gz"
    SHA1 "18e57a43efc435f2e1dae1291e82e42afbf940be"
)

project(frkhash)
set(PROJECT_VERSION 0.1.0)

cable_configure_compiler(NO_STACK_PROTECTION)
if(CABLE_COMPILER_GNULIKE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")

    option(FRKHASH_NATIVE "Build for native CPU" OFF)
    if(FRKHASH_NATIVE)
        add_compile_options(-march=native)
    endif()
elseif(MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    # For Win32 builds allow allocating more than 2 GB of memory.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
endif()

option(FRKHASH_INSTALL_CMAKE_CONFIG "Install CMake configuration scripts for find_package(CONFIG)" ON)

option(FRKHASH_FUZZING "Build with fuzzer instrumentation" OFF)
if(FRKHASH_FUZZING)
    set(CMAKE_EXE_LINKER_FLAGS "-fsanitize=fuzzer-no-link ${CMAKE_EXE_LINKER_FLAGS}")
    add_compile_options(-fno-omit-frame-pointer -fsanitize=fuzzer,undefined,integer -fno-sanitize-recover=all)
endif()

set(include_dir ${PROJECT_SOURCE_DIR}/include)

option(FRKHASH_BUILD_FRKHASH "Build frkhash::frkhash library (if NO only frkhash::keccak is built)" YES)

# cmake_dependent_option(FRKHASH_BUILD_GLOBAL_CONTEXT "Build frkhash::global-context library" YES "FRKHASH_BUILD_FRKHASH" NO)

option(FRKHASH_BUILD_TESTS "Build unit tests" YES)

add_subdirectory(lib)

if(FRKHASH_BUILD_TESTS)
    add_subdirectory(test)
endif()


install(
    DIRECTORY
    ${include_dir}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(FRKHASH_INSTALL_CMAKE_CONFIG)
    write_basic_package_version_file(frkhashConfigVersion.cmake COMPATIBILITY SameMajorVersion)
    configure_package_config_file(cmake/Config.cmake.in frkhashConfig.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/frkhash)

    install(
        EXPORT frkhashTargets
        NAMESPACE frkhash::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/frkhash
    )
    install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/frkhashConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/frkhashConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/frkhash
    )
endif()
