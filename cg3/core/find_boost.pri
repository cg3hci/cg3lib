#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

exists($$(BOOST_HOME)){
    DEFINES += CG3_WITH_BOOST
    INCLUDEPATH += -I $$(BOOST_HOME)
}
else {
    unix:!macx{
        exists(/usr/include/boost){
            DEFINES += CG3_WITH_BOOST
        }
    }

    macx{
        exists(/libs/include/boost/){
            INCLUDEPATH += -I /libs/include/boost/
            DEFINES += CG3_WITH_BOOST
        }
    }

    win32 {
        exists(C:/dev/boost){
            INCLUDEPATH += -I C:/dev/boost
            DEFINES += CG3_WITH_BOOST
        }
    }
}
