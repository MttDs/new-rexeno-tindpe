#! /bin/sh

regularFiles='/usr/rexeno/'

mkdir build
mkdir /usr/include/rexeno
cd build && cmake ../libraries && make -j 2 && make install && cd ..
cp configFiles/rexeno ~/.rexeno
cp -r protocoles/default $regularFiles



