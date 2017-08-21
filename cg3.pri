CONFIG(debug, debug|release){
    DEFINES += DEBUG
}
CONFIG(release, debug|release){
    DEFINES -= DEBUG
    #just uncomment next lines if you want to ignore asserts and got a more optimized binary
    #CONFIG += FINAL_RELEASE
}

#comment modules that you don't desire
include (cg3/core.pri)
include (cg3/meshes/dcel.pri)
include (cg3/meshes/eigenmesh.pri)
include (cg3/cgal.pri)
include (cg3/cinolib.pri)
include (cg3/libigl.pri)
include (cg3/viewer.pri)

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md


INCLUDEPATH += $$PWD
