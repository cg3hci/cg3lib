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
    $$PWD/viewer/interfaces/drawable_object.h \
    $$PWD/viewer/interfaces/pickable_object.h \
    $$PWD/viewer/interfaces/drawable_mesh.h \
    $$PWD/viewer/utilities/loadersaver.h \
    $$PWD/viewer/utilities/consolestream.h \
    $$PWD/viewer/renderable_objects/renderable_objects.h \
    $$PWD/viewer/drawable_objects/drawable_bounding_box2d.h \
    $$PWD/viewer/drawable_objects/drawable_debug_objects.h \
    $$PWD/viewer/managers/window_manager/window_manager.h

SOURCES += \
    $$PWD/viewer/glcanvas.cpp \
    $$PWD/viewer/mainwindow.cpp \
    $$PWD/viewer/interfaces/drawable_mesh.cpp \
    $$PWD/viewer/utilities/loadersaver.cpp \
    $$PWD/viewer/utilities/consolestream.cpp \
    $$PWD/viewer/drawable_objects/drawable_bounding_box2d.cpp \
    $$PWD/viewer/drawable_objects/drawable_debug_objects.cpp \
    $$PWD/viewer/managers/window_manager/window_manager.cpp \
    $$PWD/viewer/renderable_objects/renderable_objects.tpp

FORMS += \
    $$PWD/viewer/mainwindow.ui \
    $$PWD/viewer/managers/window_manager/window_manager.ui

CG3_DCEL {
    HEADERS += \
        $$PWD/viewer/drawable_objects/drawable_dcel.h \
        $$PWD/viewer/pickable_objects/pickable_dcel.h \
        $$PWD/viewer/managers/dcel_manager/dcel_manager.h

    SOURCES += \
        $$PWD/viewer/drawable_objects/drawable_dcel.cpp \
        $$PWD/viewer/pickable_objects/pickable_dcel.cpp \
        $$PWD/viewer/managers/dcel_manager/dcel_manager.cpp

    FORMS += \
        $$PWD/viewer/managers/dcel_manager/dcel_manager.ui
}

CG3_EIGENMESH {
    HEADERS += \
        $$PWD/viewer/drawable_objects/drawable_eigenmesh.h \
        $$PWD/viewer/pickable_objects/pickable_eigenmesh.h \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmesh_manager.h

    SOURCES += \
        $$PWD/viewer/drawable_objects/drawable_eigenmesh.cpp \
        $$PWD/viewer/pickable_objects/pickable_eigenmesh.cpp \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmesh_manager.cpp

    FORMS += \
        $$PWD/viewer/managers/eigenmesh_manager/eigenmesh_manager.ui

    CG3_CGAL {
        CG3_LIBIGL {
            HEADERS +=  \
                $$PWD/viewer/managers/booleans_manager/booleans_manager.h

            SOURCES += \
                $$PWD/viewer/managers/booleans_manager/booleans_manager.cpp

            FORMS += \
                $$PWD/viewer/managers/booleans_manager/booleans_manager.ui
        }
    }
}
