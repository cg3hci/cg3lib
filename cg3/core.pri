DEFINES += CG3_CORE_DEFINED
CONFIG += CG3_CORE

CONFIG += CG3_OPENMP

unix:!macx{
    QMAKE_CXXFLAGS += -std=c++11

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
    CONFIG += c++11
    
    exists(/libs/include/eigen3){
        DEFINES += CG3_WITH_EIGEN
        MODULES += CG3_WITH_EIGEN
        INCLUDEPATH += -I /libs/include/eigen3/
    }
    else{
        MODULES += CG3_WITHOUT_EIGEN
    }
}

CG3_OPENMP {
    unix:!macx{
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS += -fopenmp
    }
}

win32 {
    CONFIG += c++11

    exists(C:/dev/eigen3){
        DEFINES += CG3_WITH_EIGEN
        MODULES += CG3_WITH_EIGEN
        INCLUDEPATH += -I C:/dev/eigen3
    }
    else{
        MODULES += CG3_WITHOUT_EIGEN
    }
}

#data_structures
HEADERS += \
    $$PWD/core/cg3/data_structures/arrays.h \
    $$PWD/core/cg3/data_structures/color.h \
    $$PWD/core/cg3/data_structures/arrays/array2d.h \
    $$PWD/core/cg3/data_structures/arrays/array3d.h \
    $$PWD/core/cg3/data_structures/arrays/array4d.h \
    $$PWD/core/cg3/utilities/pair.h \
    $$PWD/core/cg3/utilities/map.h \
    $$PWD/core/cg3/geometry/2d/polygon2d.h

SOURCES += \
    $$PWD/core/cg3/data_structures/color.cpp \
    $$PWD/core/cg3/data_structures/arrays/array2d.cpp \
    $$PWD/core/cg3/data_structures/arrays/array3d.cpp \
    $$PWD/core/cg3/data_structures/arrays/array4d.cpp \
    $$PWD/core/cg3/utilities/pair.cpp \
    $$PWD/core/cg3/utilities/map.cpp \
    $$PWD/core/cg3/geometry/2d/polygon2d.cpp


##geometry
HEADERS += \
    $$PWD/core/cg3/geometry/bounding_box.h \
    $$PWD/core/cg3/geometry/line.h \
    $$PWD/core/cg3/geometry/plane.h \
    $$PWD/core/cg3/geometry/point.h \
    $$PWD/core/cg3/geometry/transformations.h \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.h \
    $$PWD/core/cg3/geometry/2d/point2d.h

SOURCES += \
    $$PWD/core/cg3/geometry/line.cpp \
    $$PWD/core/cg3/geometry/plane.cpp \
    $$PWD/core/cg3/geometry/point.cpp \
    $$PWD/core/cg3/geometry/2d/point2d.cpp

DISTFILES += \
    $$PWD/core/cg3/geometry/bounding_box.cpp \
    $$PWD/core/cg3/geometry/transformations.cpp \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.cpp

#io
HEADERS += \
    $$PWD/core/cg3/io/load_save_file.h \
    $$PWD/core/cg3/io/file_conversions.h \
    $$PWD/core/cg3/io/serializable_object.h \
    $$PWD/core/cg3/io/serialize.h

SOURCES += \
    $$PWD/core/cg3/io/load_save_file.cpp

DISTFILES += \
    $$PWD/core/cg3/io/serialize.cpp

#utilities
HEADERS += \
    $$PWD/core/cg3/utilities/comparators.h \
    $$PWD/core/cg3/utilities/const.h \
    $$PWD/core/cg3/utilities/eigen.h \
    $$PWD/core/cg3/utilities/set.h \
    $$PWD/core/cg3/utilities/string.h \
    $$PWD/core/cg3/utilities/system.h \
    $$PWD/core/cg3/utilities/vector.h \
    $$PWD/core/cg3/utilities/timer.h \
    $$PWD/core/cg3/utilities/utils.h

DISTFILES += \
    $$PWD/core/cg3/utilities/eigen.cpp \
    $$PWD/core/cg3/utilities/set.cpp \
    $$PWD/core/cg3/utilities/string.cpp \
    $$PWD/core/cg3/utilities/system.cpp \
    $$PWD/core/cg3/utilities/vector.cpp \
    $$PWD/core/cg3/timer.cpp \
    $$PWD/core/cg3/utils.cpp

INCLUDEPATH += $$PWD/core/


