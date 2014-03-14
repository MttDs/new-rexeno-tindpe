#! /bin/sh

if [ ! -d /usr/include/rexeno ];
then
    sudo mkdir /usr/include/rexeno
fi

if [ ! -d /usr/include/rexeno/matrix ];
then
    sudo mkdir /usr/include/rexeno/matrix
fi

cp matrix.cxx matrix.hh fft.cxx fft.h /usr/include/rexeno/matrix/.
