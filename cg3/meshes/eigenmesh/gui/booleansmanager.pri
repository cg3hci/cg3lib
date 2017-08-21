MODULES += CG3_BOOLEANS_MANAGER

!contains(DEFINES, CG3_VIEWER_DEFINED){
    error(BooleansManager module requires Viewer module!)
}

!contains(DEFINES, CG3_CGAL_DEFINED){
    error(BooleansManager module requires Cgal module!)
}

!contains(DEFINES, CG3_LIBIGL_DEFINED){
    error(BooleansManager module requires LibIGL installed!)
}

FORMS += \
    $$PWD/booleansmanager.ui

HEADERS += \
    $$PWD/booleansmanager.h

SOURCES += \
    $$PWD/booleansmanager.cpp
