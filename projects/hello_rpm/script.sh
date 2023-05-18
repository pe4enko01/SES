#!/bin/bash

#gcc-o имя бинрника

function add_cpp_into_sources (){ #Добавляет hello_rpm.cpp в SOURCES/
    echo "move to SOURCE"
    rm -f ./SOURCES/*
    cp hello_rpm.cpp SOURCES/

}

function add_cpp_into_build (){
    echo "move to BUILD"
    rm -f ./BUILD/*
    cp SOURCES/hello_rpm.cpp BUILD/
}

function compil (){
    echo "compil"
    pushd ./BUILD
    g++ hello_rpm.cpp -o test
    rm -f hello_rpm.cpp
    popd
}

function tar_func (){
    echo "tar"
    pushd ./RPM
    tar -cf hello_rpm_tar.tar usr
    popd
}

function rpm_func (){
    echo "rpm"
    rm -fr ./RPM/*
    mkdir -p ./RPM/usr/bin
    cp -r BUILD/test RPM/usr/bin/
    cp desc.txt RPM/
}


add_cpp_into_sources #Добавляет hello_rpm.cpp в папку SOURCES/
add_cpp_into_build #Добавляет hello_rpm.cpp в папку BUILD из SOURCES/
compil #Компилирует hello_rpm.cpp в  папке BUILD
rpm_func #Создает папки usr/bin/ и добавляет туда паку BUILD, добаляет desc.txt в папку RPM
tar_func #Архивирует папку  BUILD и дбавляет hello_rpm_tar.tar в папку RPM

