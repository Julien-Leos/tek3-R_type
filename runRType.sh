#!/usr/bin/env bash

clean()
{
    rm -rf build
    rm r-type_server
    rm r-type_client
}

re()
{
    mkdir build
    compil
}

dev()
{
    cd build ; cmake .. -G "Unix Makefiles" && cmake –build .
    make -j8
    cp r-type_server ../
    cp r-type_client ../
}

compil()
{
    cd build ; conan install .. --build=missing -s compiler.libcxx=libstdc++11 && cmake .. -G "Unix Makefiles" && cmake -build .
    make -j8
    cp bin/r-type_server ../
    cp bin/r-type_client ../
}

if [[ $1 == "clean" ]]; then
    clean
elif [[ $1 == "re" ]]; then
    re
elif [[ $1 == "dev" ]]; then
    dev
else
    compil
fi
