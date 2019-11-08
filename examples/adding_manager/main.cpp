/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <cg3/viewer/mainwindow.h>
#include "example_manager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    cg3::viewer::MainWindow mw;  //Main window, it contains QGLViewer canvas

    ExampleManager exampleManager(&mw);
    mw.addManager(&exampleManager, "Example Manager");

    mw.show();
    return app.exec();
}
