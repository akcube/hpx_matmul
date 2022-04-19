# hpx_matmul

This is my implementation of parallelized matrix multiplication using the HPX library

## Installation

1. You should have the HPX libraries installed along with a C++ compiler and CMake. 
2. Git clone the repo to your system `git clone git@github.com:akcube/hpx_matmul.git`
3. `cd` into the repo. Now create and `cd` to a folder called build. `cd hpx_matmul && mkdir build && cd build`
4. Run `cmake ..`
5. Run `make -j`

## Usage

All binaries are created in `/build/bin`. Run the driver program there.

Optional command line arguments:
    - `n` : Number of rows of matrix M_1
    - `k` : Number of columns of matrix M_1 = Number of rows of matrix M_2
    - `m` : Number of columns of matrix M_2
    - `l` : The lower bound on the randomized values
    - `r` : The upper bound on the randomized values

Note: `l <= r` must be satisfied.
The program will create two random `int` matrices and display the result of their multiplication. 

# TODO

Write tests