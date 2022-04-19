# Works with 3.11 and tested through 3.23
cmake_minimum_required(VERSION 3.11...3.23)

# Library install locations
set(HPX_INCLUDE_DIR /usr/local/include/)
set(HPX_LIBRARY_DIR /usr/local/lib)

# Project name and a few useful settings. Other commands can pick up the results
project(
  HPX_MATMUL
  VERSION 1
  DESCRIPTION "An example to demonstrate matrix-multiplication using HPX"
  LANGUAGES CXX)

# Make all the libraries created go to /build/lib/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Make all the binaries created go to /build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

# The drive program code is here
add_subdirectory(src)

# The Matrix library code is here
add_subdirectory(matlib)

