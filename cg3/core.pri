DEFINES += CG3_CORE_DEFINED
CONFIG += CG3_CORE

CONFIG += CG3_OPENMP

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
    exists(C:/dev/eigen3){
        DEFINES += CG3_WITH_EIGEN
        MODULES += CG3_WITH_EIGEN
        INCLUDEPATH += -I C:/dev/eigen3
    }
    else{
        MODULES += CG3_WITHOUT_EIGEN
    }
}

#core
HEADERS += \
    $$PWD/core/cg3/cg3lib.h

#data_structures
HEADERS += \
    $$PWD/core/cg3/data_structures/arrays.h \
    $$PWD/core/cg3/data_structures/color.h \
    $$PWD/core/cg3/data_structures/arrays/array2d.h \
    $$PWD/core/cg3/data_structures/arrays/array3d.h \
    $$PWD/core/cg3/data_structures/arrays/array4d.h

SOURCES += \
    $$PWD/core/cg3/data_structures/color.tpp \
    $$PWD/core/cg3/data_structures/arrays/array2d.tpp \
    $$PWD/core/cg3/data_structures/arrays/array3d.tpp \
    $$PWD/core/cg3/data_structures/arrays/array4d.tpp

##geometry
HEADERS += \
    $$PWD/core/cg3/geometry/bounding_box.h \
    $$PWD/core/cg3/geometry/line.h \
    $$PWD/core/cg3/geometry/plane.h \
    $$PWD/core/cg3/geometry/point.h \
    $$PWD/core/cg3/geometry/segment.h \
    $$PWD/core/cg3/geometry/transformations.h \
    $$PWD/core/cg3/geometry/utils3d.h \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.h \
    $$PWD/core/cg3/geometry/2d/point2d.h \
    $$PWD/core/cg3/geometry/2d/utils2d.h \
    $$PWD/core/cg3/geometry/2d/intersections2d.h

SOURCES += \
    $$PWD/core/cg3/geometry/bounding_box.tpp \
    $$PWD/core/cg3/geometry/line.cpp \
    $$PWD/core/cg3/geometry/plane.cpp \
    $$PWD/core/cg3/geometry/point.tpp \
    $$PWD/core/cg3/geometry/segment.tpp \
    $$PWD/core/cg3/geometry/transformations.cpp \
    $$PWD/core/cg3/geometry/utils3d.tpp \
    $$PWD/core/cg3/geometry/2d/bounding_box2d.tpp\
    $$PWD/core/cg3/geometry/2d/point2d.tpp \
    $$PWD/core/cg3/geometry/2d/utils2d.tpp \
    $$PWD/core/cg3/geometry/2d/intersections2d.cpp \

#io
HEADERS += \
    $$PWD/core/cg3/io/load_save_file.h \
    $$PWD/core/cg3/io/serializable_object.h \
    $$PWD/core/cg3/io/serialize.h

SOURCES += \
    $$PWD/core/cg3/io/load_save_file.tpp \
    $$PWD/core/cg3/io/serialize.tpp

#utilities
HEADERS += \
    $$PWD/core/cg3/utilities/comparators.h \
    $$PWD/core/cg3/utilities/const.h \
    $$PWD/core/cg3/utilities/eigen.h \
    $$PWD/core/cg3/utilities/map.h \
    $$PWD/core/cg3/utilities/pair.h \
    $$PWD/core/cg3/utilities/set.h \
    $$PWD/core/cg3/utilities/string.h \
    $$PWD/core/cg3/utilities/system.h \
    $$PWD/core/cg3/utilities/timer.h \
    $$PWD/core/cg3/utilities/vector.h \
    $$PWD/core/cg3/utilities/utils.h

SOURCES += \
    $$PWD/core/cg3/utilities/eigen.tpp \
    $$PWD/core/cg3/utilities/map.tpp \
    $$PWD/core/cg3/utilities/pair.tpp \
    $$PWD/core/cg3/utilities/set.tpp \
    $$PWD/core/cg3/utilities/string.tpp \
    $$PWD/core/cg3/utilities/system.tpp \
    $$PWD/core/cg3/utilities/timer.tpp \
    $$PWD/core/cg3/utilities/vector.tpp \
    $$PWD/core/cg3/utilities/utils.tpp

#deprecated
HEADERS += \
    $$PWD/core/cg3/deprecated/serializable_object_old.h \
    $$PWD/core/cg3/deprecated/serialize_old.h

SOURCES += \
    $$PWD/core/cg3/deprecated/serialize_old.ipp


INCLUDEPATH += $$PWD/core/


