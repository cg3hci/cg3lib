#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

!contains(DEFINES, CG3_CORE_DEFINED){
    error(Viewer module requires Core module!)
}

QT += core gui opengl xml widgets

unix:!macx{
    DEFINES += CG3_VIEWER_DEFINED
    CONFIG += CG3_VIEWER
    MODULES += CG3_VIEWER

    QMAKE_CXXFLAGS += -std=c++11

    LIBS += /usr/lib/x86_64-linux-gnu/libGLU.so
    exists (/usr/lib/x86_64-linux-gnu/libQGLViewer.so) {
        LIBS += -lQGLViewer
    }
    exists (/usr/lib/x86_64-linux-gnu/libQGLViewer-qt5.so) {
        LIBS += -lQGLViewer-qt5
    }
    LIBS += -lstdc++fs
}

macx{
    exists(/libs/frameworks/QGLViewer){
        DEFINES += CG3_VIEWER_DEFINED
        CONFIG += CG3_VIEWER
        MODULES += CG3_VIEWER

        INCLUDEPATH += -I /libs/include/boost
        INCLUDEPATH += /libs/frameworks/QGLViewer/QGLViewer.framework/Headers

        LIBS += -F/libs/frameworks/QGLViewer -framework QGLViewer
        LIBS += -libc++experimental.a
    }
}

win32 {
    QGLVIEWERPATH = C:/libs/libQGLViewer

    exists($$(QGLVIEWER_HOME)){
        QGLVIEWERPATH = $$(QGLVIEWER_HOME)
    }

    exists($$QGLVIEWERPATH){
        DEFINES += CG3_VIEWER_DEFINED
        CONFIG += CG3_VIEWER
        MODULES += CG3_VIEWER

        INCLUDEPATH += -I $$quote($$QGLVIEWERPATH)

        LIBS += -lglu32 -lopengl32

        CONFIG(debug, debug|release){
            LIBS += -L$$quote($$QGLVIEWERPATH/QGLViewer) -lQGLViewerd2
        }
        CONFIG(release, debug|release){
            LIBS += -L$$quote($$QGLVIEWERPATH/QGLViewer) -lQGLViewer2
        }
    }
}

contains(DEFINES, CG3_VIEWER_DEFINED){

    HEADERS += \
        $$PWD/viewer/glcanvas.h \
        $$PWD/viewer/mainwindow.h \
        $$PWD/viewer/drawable_objects/drawable_objects.h \
        $$PWD/viewer/interfaces/drawable_object.h \
        $$PWD/viewer/interfaces/pickable_object.h \
        $$PWD/viewer/interfaces/drawable_mesh.h \
        $$PWD/viewer/utilities/loadersaver.h \
        $$PWD/viewer/utilities/consolestream.h \
        $$PWD/viewer/renderable_objects/renderable_objects.h \
        $$PWD/viewer/renderable_objects/2d/renderable_objects2d.h \
        $$PWD/viewer/drawable_objects/2d/drawable_bounding_box2d.h \
        $$PWD/viewer/drawable_objects/2d/drawable_segment2d.h

    SOURCES += \
        $$PWD/viewer/glcanvas.cpp \
        $$PWD/viewer/mainwindow.cpp \
        $$PWD/viewer/drawable_objects/drawable_objects.cpp \
        $$PWD/viewer/interfaces/drawable_mesh.cpp \
        $$PWD/viewer/utilities/loadersaver.cpp \
        $$PWD/viewer/utilities/consolestream.tpp \
        $$PWD/viewer/drawable_objects/2d/drawable_segment2d.tpp \
        $$PWD/viewer/renderable_objects/renderable_objects.tpp \
        $$PWD/viewer/drawable_objects/2d/drawable_bounding_box2d.cpp \
        $$PWD/viewer/renderable_objects/2d/renderable_objects2d.tpp

    FORMS += \
        $$PWD/viewer/mainwindow.ui

    CG3_DCEL {
        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_dcel.h \
            $$PWD/viewer/pickable_objects/pickable_dcel.h \
            $$PWD/viewer/managers/dcel_manager.h

        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_dcel.cpp \
            $$PWD/viewer/pickable_objects/pickable_dcel.cpp \
            $$PWD/viewer/managers/dcel_manager.cpp

        FORMS += \
            $$PWD/viewer/managers/dcel_manager.ui
    }

    CG3_EIGENMESH {
        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_eigenmesh.h \
            $$PWD/viewer/pickable_objects/pickable_eigenmesh.h \
            $$PWD/viewer/managers/eigenmesh_manager.h

        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_eigenmesh.cpp \
            $$PWD/viewer/pickable_objects/pickable_eigenmesh.cpp \
            $$PWD/viewer/managers/eigenmesh_manager.cpp

        FORMS += \
            $$PWD/viewer/managers/eigenmesh_manager.ui

        contains(DEFINES, CG3_CGAL_DEFINED){
            contains(DEFINES, CG3_LIBIGL_DEFINED){
                HEADERS += \
                    $$PWD/viewer/managers/booleans_manager.h

                SOURCES += \
                    $$PWD/viewer/managers/booleans_manager.cpp

                FORMS += \
                    $$PWD/viewer/managers/booleans_manager.ui
            }
        }
    }
}
else {
    message(libQGLViewer not installed properly!)
}

HEADERS += \
    $$PWD/viewer/drawable_objects/drawable_plane.h

SOURCES += \
    $$PWD/viewer/drawable_objects/drawable_plane.cpp
