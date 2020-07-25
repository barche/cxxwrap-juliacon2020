# cxxwrap-juliacon2020

This repository hosts the tutorial files for a proposed JuliaCon 2020 workshop on [CxxWrap.jl](https://github.com/JuliaInterop/CxxWrap.jl).

## Prerequisites (do this before the workshop)

The recommended method for new users is to use Docker. If you already have a C++ development setup, you should be able to follow the manual procedure also. The demo during the workshop will use the Docker approach because it works the same way on all platforms.

### Docker dev container

* Install docker: https://docs.docker.com/get-docker/
* Install vscode: https://code.visualstudio.com
* Launch vscode and install the `ms-vscode-remote.remote-containers` extension (just enter this id in the extension searchbox and click install)
* Use the "Open repository in container" command to open https://github.com/barche/libfoo.git . **Note: This can take several minutes, it downloads a 2.7 GB docker image that includes some BinaryBuilder compiler shards** 

### Manual setup
#### Basic toolkit

Aside from a working Julia 1.4 installation, a C++17 compiler is also needed to follow along the tutorial:
* Linux: Install the packages containing g++ and CMake
* macOS: Run `xcode-select --install` and install CMake from: https://cmake.org/download/
* Windows: Install Visual Studio Community edition from https://visualstudio.microsoft.com/vs/ and make sure to activate the "Desktop development with C++" workload, with CMake activated.

#### Compile libcxxwrap-julia

Follow the instructions at the https://github.com/JuliaInterop/libcxxwrap-julia README to build `libcxxwrap-julia` from scratch, and create an override file


## Tutorial

1. Simple "libfoo" hello world style tutorial
2. More elaborate wrapping of Eigen (based on a to be updated version of the files at https://github.com/barche/cppnow2018-julia)