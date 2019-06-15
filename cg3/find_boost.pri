#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
isEmpty(BOOST_PATH) {
    exists($$(BOOST_HOME)) {
        BOOST_PATH = $$(BOOST_HOME)
    }
}

exists($$BOOST_PATH) {
    DEFINES += CG3_WITH_BOOST
    INCLUDEPATH += -I $$BOOST_PATH
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
            INCLUDEPATH += -I /libs/include/
            DEFINES += CG3_WITH_BOOST
        }
        else {
            exists(/usr/local/Cellar/boost/1.66.0/include/){
                INCLUDEPATH += -I /usr/local/Cellar/boost/1.66.0/include/
                DEFINES += CG3_WITH_BOOST
            }
        }
    }

    win32 {
        BOOST_PATH = C:/libs/boost

        exists($$BOOST_PATH){
            DEFINES += CG3_WITH_BOOST
            INCLUDEPATH += -I $$quote($$BOOST_PATH)
        }
    }
}

