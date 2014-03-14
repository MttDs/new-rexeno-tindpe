#! /bin/sh

## done (but needs to be redone)
# boost sur le site officiel
# apt-get source freeglut3-dev OK
# apt-get source libx11-dev OK
# apt-get source libfreetype6-dev OK
# apt-get source libffi-dev OK
# apt-get source qt4-qmake OK

## not copied to target
# apt-get source libqt4-designer NO
# apt-get source libqt4-dev OK
# apt-get source libpcre3-dev OK

## not done
# apt-get source libxext-dev OK
# apt-get source libxi-dev OK
# apt-get source libxau-dev OK

## installation of a apt-get sourced lib
# configuration ./configure --prefix=/home/hadrien/Bureau/Work/GITs/xenomai/newRexeno/3rdparties/linux-ububuntu-12-04-noxeno/target/xau
# make
# make install

## installation of a boost
# ./boostrap.sh
# ./b2 
# ./b2 install --prefix=

# xcb:
# apt-get install libxcb-composite0
# apt-get install xtrans-dev
# apt-get install libxext-dev
# first install xcb-proto
# apt-get source x11proto-code-dev
# apt-get install libpthread-stubs0-dev
# apt-get install python-xcbgen
# apt-get install libglu1-mesa-dev
# apt-get install libx11-dev
# apt-get install x11proto-gl-dev
# then export PKG_CONFIG_PATH=../../../target/xcb-proto/lib/pkgconfig
# apt-get source libxcb-glx0
# sudo apt-get install x11proto-dri2-dev
# sudo apt-get install libxxf86vm-dev
# sudo apt-get install libxdamage-dev
# sudo apt-get install xutils-dev
# libxt-dev: /usr/include/X11/IntrinsicP.h
# tendra: /usr/lib/TenDRA/lib/include/x5/t.api/X11/IntrinsicP.h
## properly installed
# libffi
# xau
# freeglut
# x11
# freetype
# boost
# xi
# xext
# pcre
# qt

cd boost/boost_1_48_0 && ./bootstrap.sh --prefix=../target/boost && ./b2 install && cd ../..
cd opengl/freeglut-2.6.0 && ./configure && make && cp -r && cd ../..
cd x11/libx11-1.4.99.1 && ./configure && make && cp -r && cd ../..

