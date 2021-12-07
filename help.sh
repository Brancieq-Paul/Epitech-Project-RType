#!/usr/bin/env bash

if [[ $1 = "clean" ]];
then
    if test -d "build"
    then
        rm -rf build CMakeCache.txt cmake_install.cmake CMakeFiles ./bin/*
    fi
    if test -f "bin"
    then
        rm -r bin
    fi
    if test -f "r-type_server_autogen"
    then
        rm -r r-type_server_autogen
    fi
    exit
fi
if [[ $1 = "run_c" ]];
then
    if test -f bin/r-type_client
    then
        ./bin/r-type_client $2 $3
    else
        echo "No binary found, please build it with the \"build\" COMMAND."
        echo "Would you like to do it now ? y/n"
        read answer
        if [[ $answer = "y" ]];
        then
            ./help.sh build
            ./bin/r-type_client $2 $3
        exit
        fi
    fi
    exit
fi
if [[ $1 = "run_s" ]];
then
    if test -f bin/r-type_server
    then
        ./bin/r-type_server $2 $3 $4
    else
        echo "No binary found, please build it with the \"build\" COMMAND."
        echo "Would you like to do it now ? y/n"
        read answer
        if [[ $answer = "y" ]];
        then
            ./help.sh build
        exit
        fi
    fi
    exit
fi
if [[ $1 = "build" ]];
then
    if test -d "build"
    then
        cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
        cmake --build .
    else
        echo "No CONAN LIB found, please install them with the \"install\" COMMAND."
        echo "Would you like to do it now ? y/n"
        read answer
        if [[ $answer = "y" ]];
        then
            ./help.sh install
        exit
        fi
    fi
    exit
fi
if [[ $1 = "brun" ]];
then
    ./help.sh build
    ./help.sh run
    exit
fi
if [[ $1 = "install" ]];
then
    ./help.sh clean
    mkdir build
    cd build
    conan install .. --build=missing
    cd ..
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build .
fi
if test -z $1
then
    echo -e "Add a COMMAND next to the help.sh to execute it.\n\nEX: ./help COMMAND -> ./help install\n\nCOMMAND:\ninstall : clean and reinstall conan lib and Cmake cache.\nrun_s verbose==<bool> : run server on verbose true or false\nrun_c <ip server> : run client on <ip> server\nclean : clean conan lib and Cmake cache.\n"
fi
