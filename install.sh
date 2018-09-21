#!/bin/sh

sudo apt install qtcreator qt5-default -y
sudo apt install libboost-all-dev libcgal-dev libgmp-dev libqglviewer-dev libqglviewer-dev-qt5 -y
sudo apt install git doxygen libeigen3-dev libglew-dev -y

read -p "Do you wish to install LibIGL? (Y/n)" yn
    case $yn in
        [Yy]* ) 
            cd /usr/include/
            sudo git clone --recursive https://github.com/libigl/libigl.git
            sudo chown -R $USER libigl/
            echo "export LIBIGL_HOME=/usr/include/libigl" >> ~/.profile
            cd ~
            break;;
        * ) exit;;
    esac
