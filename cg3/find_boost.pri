#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

exists($$(BOOST_HOME)) {
    BOOST_PATH = $$(BOOST_HOME)
}

exists($$BOOST_PATH) {
    DEFINES += CG3_WITH_BOOST
    MODULES += CG3_WITH_BOOST
    INCLUDEPATH += -I $$BOOST_PATH
}
else {
    !win32{
        exists(/usr/include/boost){
            DEFINES += CG3_WITH_BOOST
            MODULES += CG3_WITH_BOOST
        }
        else {
            exists(/usr/local/include/boost/){
                INCLUDEPATH += -I /usr/local/include/
                MODULES += CG3_WITH_BOOST
                DEFINES += CG3_WITH_BOOST
            }
            else {
                MODULES += CG3_WITHOUT_BOOST
            }
        }
    }

    win32 {
        exists(C:/libs/boost){
            DEFINES += CG3_WITH_BOOST
            MODULES += CG3_WITH_BOOST
            INCLUDEPATH += -I "C:/libs/boost"
            BOOST_PATH = C:/libs/boost
        }
        else {
            MODULES += CG3_WITHOUT_BOOST
        }
    }
}
