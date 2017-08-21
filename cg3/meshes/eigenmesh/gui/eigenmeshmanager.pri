MODULES +=  CG3_EIGEN_MESH_MANAGER

!contains(DEFINES, CG3_VIEWER_DEFINED){
    error(EigenMeshManager module requires Viewer module!)
}

FORMS += \
    $$PWD/eigenmeshmanager.ui

HEADERS += \
    $$PWD/eigenmeshmanager.h \
    $$PWD/drawableeigenmesh.h \
    $$PWD/pickable_eigenmesh.h

SOURCES += \
    $$PWD/eigenmeshmanager.cpp \
    $$PWD/drawableeigenmesh.cpp \
    $$PWD/pickable_eigenmesh.cpp
