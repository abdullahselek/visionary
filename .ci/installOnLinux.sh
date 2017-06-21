#!/bin/bash

if [[ $TRAVIS_OS_NAME == 'linux' ]]; then

    pwd
    sudo apt-get install build-essential
    sudo apt-get install cmake libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
    cd ~
    wget -O opencv.zip https://github.com/Itseez/opencv/archive/3.2.0.zip
    unzip opencv.zip
    wget -O opencv_contrib.zip https://github.com/Itseez/opencv_contrib/archive/3.2.0.zip
    unzip opencv_contrib.zip
    cd opencv-3.2.0
    mkdir release
    cd release
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/home/travis/opencv_contrib-3.2.0/modules ..
    make -j8
    sudo make install

fi
