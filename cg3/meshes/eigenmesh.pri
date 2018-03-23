#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_WITH_EIGEN){
    error(EigenMesh module requires Core module with Eigen!)
}

DEFINES += CG3_EIGENMESH_DEFINED
MODULES += CG3_EIGENMESH

unix:!macx{
    LIBS += -lboost_system -DBOOST_LOG_DYN_LINK -lboost_log -lboost_thread -lpthread
}

HEADERS += \
    $$PWD/eigenmesh/simpleeigenmesh.h \
    $$PWD/eigenmesh/eigenmesh.h \
    $$PWD/eigenmesh/algorithms/eigenmesh_algorithms.h


SOURCES += \
    $$PWD/eigenmesh/simpleeigenmesh.cpp \
    $$PWD/eigenmesh/eigenmesh.cpp \
    $$PWD/eigenmesh/algorithms/eigenmesh_algorithms.cpp


