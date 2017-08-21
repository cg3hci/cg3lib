DEFINES += CG3_VIEWER_DEFINED
CONFIG += CG3_VIEWER
MODULES += CG3_VIEWER

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Viewer module requires cg3_core!)
}

QT += core gui opengl xml widgets

unix:!macx{
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += /usr/lib/x86_64-linux-gnu/libGLU.so
    LIBS += -lQGLViewer
}

macx{
    CONFIG += c++11
    INCLUDEPATH += -I /libs/include/boost
    INCLUDEPATH += /libs/frameworks/QGLViewer/QGLViewer.framework/Headers
    LIBS += -F/libs/frameworks/QGLViewer -framework QGLViewer
}

win32 {
    INCLUDEPATH += -I "C:/dev/libQGLViewer"

    LIBS += -lglu32 -lopengl32

    CONFIG(debug, debug|release){
        LIBS += -L"C:/dev/libQGLViewer/QGLViewer" -lQGLViewerd2
    }
    CONFIG(release, debug|release){
        LIBS += -L"C:/dev/libQGLViewer/QGLViewer" -lQGLViewer2
    }
}

HEADERS += \
    $$PWD/viewer/glcanvas.h \
    $$PWD/viewer/mainwindow.h \
    $$PWD/viewer/objects/drawabledebugobjects.h \
    $$PWD/viewer/managers/window_manager/windowmanager.h \
    $$PWD/viewer/objects/objects.h \
    $$PWD/viewer/interfaces/drawable_object.h \
    $$PWD/viewer/interfaces/pickable_object.h \
    $$PWD/viewer/interfaces/drawable_mesh.h \
    $$PWD/viewer/drawable_objects/drawableboundingbox2d.h \
    $$PWD/viewer/utilities/loadersaver.h \
    $$PWD/viewer/utilities/consolestream.h

SOURCES += \
    $$PWD/viewer/glcanvas.cpp \
    $$PWD/viewer/mainwindow.cpp \
    $$PWD/viewer/objects/drawabledebugobjects.cpp \
    $$PWD/viewer/managers/window_manager/windowmanager.cpp \
    $$PWD/viewer/interfaces/drawable_mesh.cpp \
    $$PWD/viewer/drawable_objects/drawableboundingbox2d.cpp \
    $$PWD/viewer/utilities/loadersaver.cpp \
    $$PWD/viewer/utilities/consolestream.cpp

DISTFILES += \
    $$PWD/viewer/objects/objects.cpp

FORMS += \
    $$PWD/viewer/mainwindow.ui \
    $$PWD/viewer/managers/window_manager/windowmanager.ui

CG3_DCEL {
    HEADERS += \
        $$PWD/viewer/managers/dcel_manager/dcelmanager.h \
        $$PWD/viewer/managers/dcel_manager/drawable_dcel.h \
        $$PWD/viewer/managers/dcel_manager/pickable_dcel.h

    SOURCES += \
        $$PWD/viewer/managers/dcel_manager/dcelmanager.cpp \
        $$PWD/viewer/managers/dcel_manager/drawable_dcel.cpp \
        $$PWD/viewer/managers/dcel_manager/pickable_dcel.cpp

    FORMS += \
        $$PWD/viewer/managers/dcel_manager/dcelmanager.ui
}

CG3_EIGENMESH {
    HEADERS += \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmeshmanager.h \
        $$PWD/viewer/managers/eigenmesh_manager/drawable_eigenmesh.h \
        $$PWD/viewer/managers/eigenmesh_manager/pickable_eigenmesh.h

    SOURCES += \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmeshmanager.cpp \
        $$PWD/viewer/managers/eigenmesh_manager/drawable_eigenmesh.cpp \
        $$PWD/viewer/managers/eigenmesh_manager/pickable_eigenmesh.cpp

    FORMS += \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmeshmanager.ui

    CG3_CGAL {
        CG3_LIBIGL {
            HEADERS += \
                $$PWD/viewer/managers/booleans_manager/booleansmanager.h

            SOURCES += \
                $$PWD/viewer/managers/booleans_manager/booleansmanager.cpp

            FORMS += \
                $$PWD/viewer/managers/booleans_manager/booleansmanager.ui
        }
    }
}
