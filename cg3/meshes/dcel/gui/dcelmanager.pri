MODULES += CG3_DCEL_MANAGER

!contains(DEFINES, CG3_VIEWER_DEFINED){
    error(DcelManager module requires Viewer module!)
}

HEADERS += \
    $$PWD/dcelmanager.h \
    $$PWD/drawable_dcel.h \
    $$PWD/pickable_dcel.h

SOURCES += \
    $$PWD/dcelmanager.cpp \
    $$PWD/drawable_dcel.cpp \
    $$PWD/pickable_dcel.cpp

FORMS += \
    $$PWD/dcelmanager.ui
