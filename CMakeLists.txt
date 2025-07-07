# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(thesis_project)

#To pira apo to magic wand sample, Pithanos na to xreiastw kai sto diko moy project.
# These samples use local static initialization. Since Zephyr doesn't support the
# C++ ABI for thread-safe initialization of local statics and the constructors don't
# appear to require thread safety, we turn it off in the C++ compiler.
set(NO_THREADSAFE_STATICS $<TARGET_PROPERTY:compiler-cpp,no_threadsafe_statics>)
zephyr_compile_options($<$<COMPILE_LANGUAGE:CXX>:${NO_THREADSAFE_STATICS}>)

list(APPEND EXTRA_ZEPHYR_MODULES
    ${ZEPHYR_TFLITE_MODULE_DIR}           # Links TFLite Micro library
)

target_sources(app PRIVATE
    src/main.cc
    src/constants.cc
    src/gesture_model.cc
    src/model_data.cc
    src/output_handler.cc
)