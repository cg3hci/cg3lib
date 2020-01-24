#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

EIGEN_ENV_VARIABLE = $$(EIGEN_HOME)

isEmpty(EIGEN_PATH):!isEmpty(EIGEN_ENV_VARIABLE):exists($$EIGEN_ENV_VARIABLE) {
    EIGEN_PATH = $$EIGEN_ENV_VARIABLE
}

!isEmpty(EIGEN_PATH):exists($$EIGEN_PATH) {
    DEFINES += CG3_WITH_EIGEN
    MODULES += CG3_WITH_EIGEN
    INCLUDEPATH += -I $$EIGEN_PATH
}
else {
    unix{
        exists(/usr/include/eigen3){ #linux apt default
            DEFINES += CG3_WITH_EIGEN
            MODULES += CG3_WITH_EIGEN
            INCLUDEPATH += -I /usr/include/eigen3
        }
        else{
            exists(/usr/local/include/eigen3){ #mac brew default
                DEFINES += CG3_WITH_EIGEN
                MODULES += CG3_WITH_EIGEN
                INCLUDEPATH += -I /usr/local/include/eigen3/
            }
            else {
                MODULES += CG3_WITHOUT_EIGEN
            }
        }
    }

    win32 {
        exists(C:/libs/eigen3){
            DEFINES += CG3_WITH_EIGEN
            MODULES += CG3_WITH_EIGEN
            INCLUDEPATH += -I "C:/libs/eigen3"
            EIGEN_PATH = C:/libs/eigen3
        }
        else{
            MODULES += CG3_WITHOUT_EIGEN
        }
    }
}
