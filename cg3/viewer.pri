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
    QGLVIEWER_PATH = /usr/local/lib

    QGLVIEWER_ENV_VARIABLE = $$(QGLVIEWER_HOME)

    !isEmpty(QGLVIEWER_ENV_VARIABLE):exists($$QGLVIEWER_ENV_VARIABLE) {
        QGLVIEWER_PATH = $$QGLVIEWER_ENV_VARIABLE
    }

    !isEmpty(QGLVIEWER_PATH):exists($$QGLVIEWER_PATH) {
        DEFINES += CG3_VIEWER_DEFINED
        CONFIG += CG3_VIEWER
        MODULES += CG3_VIEWER

        INCLUDEPATH += $$QGLVIEWER_PATH/QGLViewer.framework/Headers

        TARGETPATH = $${TARGET}.app/Contents/MacOS/$${TARGET}
        !isEmpty(DESTDIR) {
            TARGETPATH = $${DESTDIR}/$${TARGET}.app/Contents/MacOS/$${TARGET}
        }

        exists($$QGLVIEWER_PATH/QGLViewer.framework) {
            !plugin:QMAKE_POST_LINK=install_name_tool -change QGLViewer.framework/Versions/2/QGLViewer $$QGLVIEWER_PATH/QGLViewer.framework/Versions/2/QGLViewer $$TARGETPATH #VERSION_MAJOR
            LIBS += -F$$QGLVIEWER_PATH -framework QGLViewer
        } else {
            !plugin:QMAKE_POST_LINK=install_name_tool -change libQGLViewer.2.dylib $$QGLVIEWER_PATH/libQGLViewer.2.dylib $$TARGETPATH #VERSION_MAJOR
            LIBS *= -L$$QGLVIEWER_PATH -lQGLViewer
        }

        #LIBS += -libc++experimental.a
    }
}

win32 {
    QGLVIEWER_PATH = C:/libs/libQGLViewer

    QGLVIEWER_ENV_VARIABLE = $$(QGLVIEWER_HOME)

    !isEmpty(QGLVIEWER_ENV_VARIABLE):exists($$QGLVIEWER_ENV_VARIABLE) {
        QGLVIEWER_PATH = $$QGLVIEWER_ENV_VARIABLE
    }

    !isEmpty(QGLVIEWER_PATH):exists($$QGLVIEWER_PATH) {
        DEFINES += CG3_VIEWER_DEFINED
        CONFIG += CG3_VIEWER
        MODULES += CG3_VIEWER

        INCLUDEPATH += -I $$quote($$QGLVIEWER_PATH)

        LIBS += -lglu32 -lopengl32

        CONFIG(debug, debug|release){
            LIBS += -L$$quote($$QGLVIEWER_PATH/QGLViewer) -lQGLViewerd2
        }
        CONFIG(release, debug|release){
            LIBS += -L$$quote($$QGLVIEWER_PATH/QGLViewer) -lQGLViewer2
        }
    }
}

contains(DEFINES, CG3_VIEWER_DEFINED){
    HEADERS += \
        $$PWD/viewer/viewer.h \
        $$PWD/viewer/glcanvas.h \
        $$PWD/viewer/mainwindow.h \
        $$PWD/viewer/drawable_objects/drawable_arrow3.h \
        $$PWD/viewer/drawable_objects/drawable_bounding_box2.h \
        $$PWD/viewer/drawable_objects/drawable_bounding_box3.h \
        $$PWD/viewer/drawable_objects/drawable_cylinder.h \
        $$PWD/viewer/drawable_objects/drawable_mixed_objects.h \
        $$PWD/viewer/drawable_objects/drawable_objects_container.h \
        $$PWD/viewer/drawable_objects/drawable_point2.h \
        $$PWD/viewer/drawable_objects/drawable_point3.h \
        $$PWD/viewer/drawable_objects/drawable_polygon2.h \
        $$PWD/viewer/drawable_objects/drawable_segment2.h \
        $$PWD/viewer/drawable_objects/drawable_segment3.h \
        $$PWD/viewer/drawable_objects/drawable_sphere.h \
        $$PWD/viewer/drawable_objects/drawable_plane.h \
        $$PWD/viewer/drawable_objects/drawable_triangle3.h \
        $$PWD/viewer/interfaces/abstract_mainwindow.h \
        $$PWD/viewer/interfaces/drawable_container.h \
        $$PWD/viewer/interfaces/drawable_object.h \
        $$PWD/viewer/interfaces/manipulable_object.h \
        $$PWD/viewer/interfaces/pickable_object.h \
        $$PWD/viewer/interfaces/drawable_mesh.h \
        $$PWD/viewer/opengl_objects/opengl_objects2.h \
        $$PWD/viewer/opengl_objects/opengl_objects3.h \
        $$PWD/viewer/utilities/loadersaver.h \
        $$PWD/viewer/utilities/console_stream.h \
        $$PWD/viewer/utilities/utils.h \
        $$PWD/viewer/widgets/qclickablelabel.h \
        $$PWD/viewer/internal/drawable_mesh_drawlist_manager.h \
        $$PWD/viewer/internal/drawable_container_drawlist_manager.h \
        $$PWD/viewer/internal/drawable_object_drawlist_manager.h \
        $$PWD/viewer/internal/manipulable_object_drawlist_manager.h \
        $$PWD/viewer/internal/submanager.h

    CG3_STATIC {
    SOURCES += \
        $$PWD/viewer/glcanvas.cpp \
        $$PWD/viewer/mainwindow.cpp \
        $$PWD/viewer/drawable_objects/drawable_arrow3.cpp \
        $$PWD/viewer/drawable_objects/drawable_bounding_box2.cpp \
        $$PWD/viewer/drawable_objects/drawable_bounding_box3.cpp \
        $$PWD/viewer/drawable_objects/drawable_cylinder.cpp \
        $$PWD/viewer/drawable_objects/drawable_mixed_objects.cpp \
        $$PWD/viewer/drawable_objects/drawable_objects_container.cpp \
        $$PWD/viewer/drawable_objects/drawable_plane.cpp \
        $$PWD/viewer/drawable_objects/drawable_point2.cpp \
        $$PWD/viewer/drawable_objects/drawable_point3.cpp \
        $$PWD/viewer/drawable_objects/drawable_polygon2.cpp \
        $$PWD/viewer/drawable_objects/drawable_segment2.cpp \
        $$PWD/viewer/drawable_objects/drawable_segment3.cpp \
        $$PWD/viewer/drawable_objects/drawable_sphere.cpp \
        $$PWD/viewer/drawable_objects/drawable_triangle3.cpp \
        $$PWD/viewer/interfaces/drawable_container.cpp \
        $$PWD/viewer/interfaces/drawable_mesh.cpp \
        $$PWD/viewer/interfaces/manipulable_object.cpp \
        $$PWD/viewer/internal/drawable_container_drawlist_manager.cpp \
        $$PWD/viewer/internal/drawable_mesh_drawlist_manager.cpp \
        $$PWD/viewer/internal/drawable_object_drawlist_manager.cpp \
        $$PWD/viewer/internal/manipulable_object_drawlist_manager.cpp \
        $$PWD/viewer/opengl_objects/opengl_objects2.cpp \
        $$PWD/viewer/opengl_objects/opengl_objects3.cpp \
        $$PWD/viewer/utilities/console_stream.cpp \
        $$PWD/viewer/utilities/loadersaver.cpp \
        $$PWD/viewer/utilities/utils.cpp \
        $$PWD/viewer/widgets/qclickablelabel.cpp
    }

    SOURCES +=  \
        $$PWD/viewer/interfaces/pickable_object.cpp

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
            $$PWD/viewer/drawable_objects/drawable_voronoi_diagram3.h
        CG3_STATIC {
        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_voronoi_diagram3.cpp
        }
    }

    contains(DEFINES, CG3_DCEL_DEFINED) {
        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_dcel.h \
            $$PWD/viewer/pickable_objects/pickable_dcel.h \
            $$PWD/viewer/managers/dcel_manager.h

        CG3_STATIC {
        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_dcel.cpp \
            $$PWD/viewer/managers/dcel_manager.cpp \
            $$PWD/viewer/pickable_objects/pickable_dcel.cpp
        }

        FORMS += \
            $$PWD/viewer/managers/dcel_manager.ui
    }

    contains(DEFINES, CG3_EIGENMESH_DEFINED) {
        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_eigenmesh.h \
            $$PWD/viewer/pickable_objects/pickable_eigenmesh.h \
            $$PWD/viewer/managers/eigenmesh_manager.h

        CG3_STATIC {
        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_eigenmesh.cpp \
            $$PWD/viewer/managers/eigenmesh_manager.cpp \
            $$PWD/viewer/pickable_objects/pickable_eigenmesh.cpp
        }

        FORMS += \
            $$PWD/viewer/managers/eigenmesh_manager.ui

        contains(DEFINES, CG3_CGAL_DEFINED){
            contains(DEFINES, CG3_LIBIGL_DEFINED){
                HEADERS += \
                    $$PWD/viewer/managers/booleans_manager.h

                CG3_STATIC {
                SOURCES += \
                    $$PWD/viewer/managers/booleans_manager.cpp
                }

                FORMS += \
                    $$PWD/viewer/managers/booleans_manager.ui
            }
        }
    }

    contains(DEFINES, CG3_CINOLIB_DEFINED) {
        DEFINES        += CINOLIB_USES_OPENGL
        DEFINES        += CINOLIB_USES_QT

        unix:!macx {
            DEFINES += GL_GLEXT_PROTOTYPES
            LIBS    += -lGLU
        }

        HEADERS += \
            $$PWD/viewer/drawable_objects/drawable_tetmesh.h

        CG3_STATIC {
        SOURCES += \
            $$PWD/viewer/drawable_objects/drawable_tetmesh.cpp
        }
    }
}
else {
    message(libQGLViewer not installed properly!)
}
