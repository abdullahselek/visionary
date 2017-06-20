#!/bin/bash

if [[ $TRAVIS_OS_NAME == 'osx' ]]; then

    brew update
    brew tap homebrew/science
    rm -rf /usr/local/bin/f2py
    rm -rf /usr/local/lib/python2.7
    brew install opencv3 --with-contrib --with-ffmpeg
    echo 'export PATH="/usr/local/opt/opencv3/bin:$PATH"' >> ~/.bash_profile
    source ~/.bash_profile

fi
