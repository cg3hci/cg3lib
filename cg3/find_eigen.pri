#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
isEmpty(EIGEN_PATH) {
    exists($$(EIGEN_HOME)) {
        EIGEN_PATH = $$(EIGEN_HOME)
    }
}

exists($$EIGEN_PATH) {
    DEFINES += CG3_WITH_EIGEN
    MODULES += CG3_WITH_EIGEN
    INCLUDEPATH += -I $$EIGEN_PATH
}
else {
    unix:!macx{
        exists(/usr/include/eigen3){
            DEFINES += CG3_WITH_EIGEN
            MODULES += CG3_WITH_EIGEN
            INCLUDEPATH += -I /usr/include/eigen3
        }
        else{
            MODULES += CG3_WITHOUT_EIGEN
        }
    }

    macx{
        exists(/libs/include/eigen3){
            DEFINES += CG3_WITH_EIGEN
            MODULES += CG3_WITH_EIGEN
            INCLUDEPATH += -I /libs/include/eigen3/
        }
        else {
            exists(/usr/local/Cellar/eigen/3.3.4/include/eigen3){
                DEFINES += CG3_WITH_EIGEN
                MODULES += CG3_WITH_EIGEN
                INCLUDEPATH += -I /usr/local/Cellar/eigen/3.3.4/include/eigen3
            }
            else{
                MODULES += CG3_WITHOUT_EIGEN
            }
        }

    }

    win32 {
        EIGEN_PATH = C:/libs/eigen3

        exists($$EIGEN_PATH){
            DEFINES += CG3_WITH_EIGEN
            MODULES += CG3_WITH_EIGEN
            INCLUDEPATH += -I $$quote($$EIGEN_PATH)
        }
        else{
            MODULES += CG3_WITHOUT_EIGEN
        }
    }
}
