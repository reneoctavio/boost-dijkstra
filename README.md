# Dijstra Single Source Shortest Path

## Requirements

1. A C++ compiler
2. Boost library

## Build

- clang: `clang++ src/main.cpp -o main`
- g++: `g++ src/main.cpp -o main`

## Run

- Command: `./main [d|m] <file>`
- Arg 1: `d` for Dimacs or `m` for Matrix Market
- Arg 2: path to file
- Example: `./main m /path/to/graph.mtx`
- Will create a distance.mtx in the directory that was run

## License

Licensed under GPLv3.
