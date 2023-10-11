## This is a shell script to download, compile and build Google unit test
## case framework (version 1.14.0) on MacOS X and later. It also copies
## over the necessary libraries and header files to the respective system path 
## so that the test framework is available for any project. After that it cleans
## up the downloaded folder and unnecessary files.
## The credit goes to 
## https://gist.github.com/butuzov/e7df782c31171f9563057871d0ae444a basically.
## It is a modified one of the original script in accordence to the latest 
## version and build structure on MacOS Ventura.

#!/usr/bin/env bash

## Current directory
CURR_DIR=$(pwd)

## Download the 1.14.0 release version to the disc and unpack it
function download {
    printf "\n Downloading and unpacking GoogleTest framework 1.14.0\n\n..."
    curl -LO https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    tar xf v1.14.0.tar.gz
}

## Build and compile it
function build {
    printf "\n Building GTEST and GMOCK...\n\n"
    cd googletest-1.14.0
    mkdir build
    cd $_
    cmake -Dgtest_build_samples=OFF -Dgtest_build_tests=OFF ../
    make
    sudo chown -R `whoami`:admin /usr/local/include/
    sudo make install
}

## Cleaning up
function cleanup {
    printf "\n  Running Cleanup\n\n"
    cd $CURR_DIR
    rm -rf googletest-1.14.0
    unlink v1.14.0.tar.gz
}

download && build && cleanup

exit 0
