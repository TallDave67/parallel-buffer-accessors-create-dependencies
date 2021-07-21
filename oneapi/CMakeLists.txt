cmake_minimum_required(VERSION 3.16)
project(buffer-accessors-create-dependencies)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(buffer-accessors-create-dependencies
  buffer-accessors-create-dependencies.cpp
)

target_compile_options(buffer-accessors-create-dependencies PRIVATE 
  -std=c++20 -stdlib=libstdc++
)

