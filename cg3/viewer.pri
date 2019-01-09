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
        $$PWD/viewer/viewer.h \
        $$PWD/viewer/glcanvas.h \
        $$PWD/viewer/mainwindow.h \
        $$PWD/viewer/drawable_objects/drawable_bounding_box.h \
        $$PWD/viewer/drawable_objects/drawable_cylinder.h \
        $$PWD/viewer/drawable_objects/drawable_objects_container.h\
        $$PWD/viewer/drawable_objects/drawable_sphere.h \
        $$PWD/viewer/drawable_objects/drawable_plane.h \
        $$PWD/viewer/drawable_objects/drawable_point.h \
        $$PWD/viewer/drawable_objects/drawable_segment.h \
        $$PWD/viewer/drawable_objects/drawable_triangle.h \
        $$PWD/viewer/drawable_objects/drawable_mixed_objects.h \
        $$PWD/viewer/drawable_objects/2d/drawable_bounding_box2d.h \
        $$PWD/viewer/drawable_objects/2d/drawable_polygon2d.h \
        $$PWD/viewer/drawable_objects/2d/drawable_segment2d.h \
        $$PWD/viewer/interfaces/drawable_container.h \
        $$PWD/viewer/interfaces/drawable_object.h \
        $$PWD/viewer/interfaces/manipulable_object.h \
        $$PWD/viewer/interfaces/pickable_object.h \
        $$PWD/viewer/interfaces/drawable_mesh.h \
        $$PWD/viewer/internal/drawable_mesh_drawlist_manager.h \
        $$PWD/viewer/internal/drawable_container_drawlist_manager.h \
        $$PWD/viewer/internal/drawable_object_drawlist_manager.h \
        $$PWD/viewer/internal/manipulable_object_drawlist_manager.h \
        $$PWD/viewer/internal/submanager.h \
        $$PWD/viewer/opengl_objects/opengl_objects.h \
        $$PWD/viewer/opengl_objects/2d/opengl_objects2d.h \
        $$PWD/viewer/utilities/loadersaver.h \
        $$PWD/viewer/utilities/console_stream.h \
        $$PWD/viewer/utilities/utils.h \
        $$PWD/viewer/widgets/qclickablelabel.h

    SOURCES += \
        $$PWD/viewer/glcanvas.cpp \
        $$PWD/viewer/mainwindow.cpp \
        $$PWD/viewer/drawable_objects/drawable_bounding_box.cpp \
        $$PWD/viewer/drawable_objects/drawable_cylinder.cpp \
        $$PWD/viewer/drawable_objects/drawable_objects_container.tpp \
        $$PWD/viewer/drawable_objects/drawable_sphere.cpp \
        $$PWD/viewer/drawable_objects/drawable_plane.cpp \
        $$PWD/viewer/drawable_objects/drawable_point.cpp \
        $$PWD/viewer/drawable_objects/drawable_segment.cpp \
        $$PWD/viewer/drawable_objects/drawable_triangle.cpp \
        $$PWD/viewer/drawable_objects/drawable_mixed_objects.cpp \
        $$PWD/viewer/drawable_objects/2d/drawable_bounding_box2d.cpp \
        $$PWD/viewer/drawable_objects/2d/drawable_polygon2d.cpp \
        $$PWD/viewer/drawable_objects/2d/drawable_segment2d.cpp \
        $$PWD/viewer/interfaces/drawable_container.cpp \
        $$PWD/viewer/interfaces/drawable_mesh.cpp \
        $$PWD/viewer/interfaces/manipulable_object.cpp \
        $$PWD/viewer/interfaces/pickable_object.cpp \
        $$PWD/viewer/internal/drawable_mesh_drawlist_manager.cpp \
        $$PWD/viewer/internal/drawable_container_drawlist_manager.cpp \
        $$PWD/viewer/internal/drawable_object_drawlist_manager.cpp \
        $$PWD/viewer/internal/manipulable_object_drawlist_manager.cpp \
        $$PWD/viewer/opengl_objects/opengl_objects.tpp \
        $$PWD/viewer/opengl_objects/2d/opengl_objects2d.tpp \
        $$PWD/viewer/utilities/console_stream.cpp \
        $$PWD/viewer/utilities/loadersaver.cpp \
        $$PWD/viewer/utilities/utils.cpp \
        $$PWD/viewer/widgets/qclickablelabel.cpp


    FORMS += \
        $$PWD/viewer/mainwindow.ui \
        $$PWD/viewer/internal/drawable_mesh_drawlist_manager.ui \
        $$PWD/viewer/internal/drawable_container_drawlist_manager.ui \
        $$PWD/viewer/internal/drawable_object_drawlist_manager.ui \
        $$PWD/viewer/internal/manipulable_object_drawlist_manager.ui

    RESOURCES += \
        $$PWD/viewer/internal/icons/icons.qrc

    contains(DEFINES, CG3_VORO_DEFINED) {
        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_voronoi_diagram.h

        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_voronoi_diagram.cpp
    }

    contains(DEFINES, CG3_DCEL_DEFINED) {
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

    contains(DEFINES, CG3_EIGENMESH_DEFINED) {
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

    CG3_CINOLIB {
        DEFINES        += CINOLIB_USES_OPENGL
        DEFINES        += CINOLIB_USES_QT

        unix:!macx {
            DEFINES += GL_GLEXT_PROTOTYPES
            LIBS    += -lGLU
        }

        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_tetmesh.h \
            $$PWD/viewer/internal/drawable_tetmesh_drawlist_manager.h \
            $$PWD/viewer/widgets/drawable_tetmesh_control_panel.h

        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_tetmesh.cpp \
            $$PWD/viewer/internal/drawable_tetmesh_drawlist_manager.cpp \
            $$PWD/viewer/widgets/drawable_tetmesh_control_panel.cpp

        FORMS += \
            $$PWD/viewer/internal/drawable_tetmesh_drawlist_manager.ui \
        $$PWD/viewer/widgets/drawable_tetmesh_control_panel.ui
    }
}
else {
    message(libQGLViewer not installed properly!)
}
