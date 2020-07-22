# cxxwrap-juliacon2020
Tutorial files for the JuliaCon 2020 CxxWrap workshop (should it be accepted)

This repository will host the tutorial files for a proposed JuliaCon 2020 workshop on [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl).

## Prerequisites

### Basic toolkit

Aside from a working Julia 1.4 installation, a C++17 compiler is also needed to follow along the tutorial:
* Linux: Install the packages containing g++ and CMake
* macOS: Run `xcode-select --install` and install CMake from: https://cmake.org/download/
* Windows: Install Visual Studio Community edition from https://visualstudio.microsoft.com/vs/ and make sure to activate the "Desktop development with C++" workload, with CMake activated.

### Compile libcxxwrap-julia

Follow the instructions at the https://github.com/JuliaInterop/libcxxwrap-julia README to build `libcxxwrap-julia` from scratch, and create an override file

### Alternative methods (to be elaborated)
* Use BinaryBuilder even for local development
* Use the Julia dev container (see https://discourse.julialang.org/t/compile-julia-from-source-with-ease-in-vs-code-even-on-windows/35696)

## Tutorial

1. Simple "libfoo" hello world style tutorial
2. More elaborate wrapping of Eigen (based on a to be updated version of the files at https://github.com/barche/cppnow2018-julia)