/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  * @author Marco Livesu (marco.livesu@gmail.com)
  */

#ifndef CG3_MAINWINDOW_H
#define CG3_MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QToolBox>
#include <QFrame>
#include <QSignalMapper>
#include <QCheckBox>
#include <QProcess>
#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif
#include <boost/bimap.hpp>
#ifdef __APPLE__
#pragma clang diagnostic pop
#endif
#include <QApplication>

#include "interfaces/drawable_object.h"
#include "interfaces/pickable_object.h"
#include "utilities/loadersaver.h"
#include <cg3/geometry/bounding_box.h>
#include "drawable_objects/drawable_debug_objects.h"
#include "utilities/consolestream.h"
#include <cg3/geometry/2d/point2d.h>

namespace Ui {
    class MainWindow;
}

/**
 * @brief La classe MainWindow è una classe che gestisce la canvas di QGLViewer e tutti i manager che vengono aggiunti ad essa.
 *
 * Gestisce in oltre una scrollArea avente le checkbox che gestiscono la visualizzazione di tutti gli oggetti presenti nella canvas.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void fitScene();
        void fitScene(const cg3::Pointd& center, double radius);
        cg3::Point2Di getCanvasSize() const;
        void updateGlCanvas();
        void pushObj(const cg3::DrawableObject * obj, std::string checkBoxName, bool b = true);
        void deleteObj(const cg3::DrawableObject * obj, bool b = true);
        void setObjVisibility(const cg3::DrawableObject * obj, bool visible);
        bool contains(const cg3::DrawableObject* obj);
        cg3::BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();
        void saveSnapshot();
        void drawAxis(bool);

        void savePointOfView();
        void loadPointOfView();
        void savePointOfView(std::string filename);
        void loadPointOfView(std::string filename);

        void setFullScreen(bool);
        void setBackgroundColor(const QColor &);

        int addManager(QFrame *f, std::string name, QToolBox *parent = nullptr);
        QFrame *getManager(unsigned int i);
        void renameManager(unsigned int i, std::string s);
        void setCurrentIndexToolBox(unsigned int i);

        void disableRotation();
        void enableRotation();
        void disableTranslation();
        void enableTranslation();
        void disableZoom();
        void enableZoom();
        void setSelectLeftButton();

        void enableDebugObjects();
        void disableDebugObjects();
        void addDebugSphere(const cg3::Pointd& center, double radius, const QColor &color, int precision = 4);
        void clearDebugSpheres();
        void addDebugCylinder(const cg3::Pointd& a, const cg3::Pointd& b, double radius, const QColor color);
        void clearDebugCylinders();
        void addDebugLine(const cg3::Pointd& a, const cg3::Pointd& b, int width, const QColor color);
        void clearDebugLines();

        void toggleConsoleStream();

        void keyPressEvent(QKeyEvent * event);

    signals:
        /**
         * @brief objectClicked
         * Segnale da "catchare", ha come parametro l'oggetto cliccato nella GLCanvas
         */
        void objectPicked(unsigned int);
        void point2DClicked(cg3::Point2Dd);

        /**
         * @brief undoEvent
         * Segnale da "catchare", viene lanciato quando viene premuto CTRL+Z
         */
        void undoEvent();

        /**
         * @brief undoEvent
         * Segnale da "catchare", viene lanciato quando viene premuto MAIUSC+CTRL+Z
         */
        void redoEvent();

    private slots:
        void checkBoxClicked(int i);
        void slotObjectPicked(unsigned int i);
        void slotPoint2DClicked(cg3::Point2Dd p);

        void on_actionSave_Snapshot_triggered();

        void on_actionShow_Axis_triggered();

        void on_actionFull_Screen_toggled(bool arg1);

        void on_actionUpdate_Canvas_triggered();

        void on_actionFit_Scene_triggered();

        void on_actionChange_Background_Color_triggered();

        void on_actionSave_Point_Of_View_triggered();

        void on_actionLoad_Point_of_View_triggered();

        void on_actionShow_Hide_Dock_Widget_triggered();

        void on_actionLoad_Point_Of_View_from_triggered();

        void on_actionSave_Point_Of_View_as_triggered();

        void on_actionShow_Hide_Console_Stream_triggered();

private:

        // GUI
        //
        Ui::MainWindow  * ui;
        std::vector<QFrame *> managers;
        cg3::viewer::LoaderSaver povLS;
        ConsoleStream* consoleStream;

        //Config
        //
        #ifdef WIN32
        const std::string configFolderDirectory = std::string(std::getenv("USERPROFILE")) + "\\AppData\\Roaming\\cg3lib\\";
        #elif __APPLE__
        const std::string configFolderDirectory = std::string("/Users/") + std::getenv("USER") + "/Library/Preferences/cg3lib/"
        #elif __linux__
        const std::string configFolderDirectory = std::string(std::getenv("HOME")) + "/.config/cg3lib/";
        #endif

        // Mesh Stack
        //
        QSignalMapper* checkBoxMapper;
        std::map<int, QCheckBox * > checkBoxes;
        boost::bimap<int, const cg3::DrawableObject*> mapObjects;
        int nMeshes;
        bool first;
        cg3::DrawableDebugObjects* debugObjects;
};

#endif // CG3_MAINWINDOW_H
