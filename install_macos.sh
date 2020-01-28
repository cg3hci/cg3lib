#!/bin/bash

#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
#

#
# This script installs all the dependencies of cg3lib in a
# MacOS system.
#
# Tested with MacOS 10.14
#
# requires: brew
#

brew install git qt boost eigen cgal llvm

echo "export QTDIR=/usr/local/opt/qt" >> ~/.bash_profile
echo "export PATH=$QTDIR/bin:$PATH" >> ~/.bash_profile
echo "export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH" >> ~/.bash_profile
echo "export PKG_CONFIG_PATH=$QTDIR/lib:$PKG_CONFIG_PATH" >> ~/.bash_profile
. ~/.bash_profile

cd /usr/local/opt
git clone https://github.com/GillesDebunne/libQGLViewer.git
cd libQGLViewer/QGLViewer
/usr/local/opt/qt/bin/qmake #-spec macx-clang #spec doesn't work on GitHub actions
make 
make install  
echo "export QGLVIEWER_HOME=/usr/local/lib" >> ~/.bash_profile #here is installed QGLViewer.framework
cd ..
cd ..

git clone --recursive https://github.com/libigl/libigl
echo "export LIBIGL_HOME=/usr/local/opt/libigl" >> ~/.bash_profile
git clone --depth=1 --branch=devel https://github.com/cnr-isti-vclab/vcglib.git
echo "export VCGLIB_HOME=/usr/local/opt/vcglib" >> ~/.bash_profile
git clone https://github.com/mlivesu/cinolib.git
echo "export CINOLIB_HOME=/usr/local/opt/cinolib" >> ~/.bash_profile
. ~/.bash_profile
