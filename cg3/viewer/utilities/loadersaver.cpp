/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "loadersaver.h"

#include <QFileDialog>
#include <cg3/utilities/string.h>

namespace cg3 {

namespace viewer {

/**
 * @brief LoaderSaver::LoaderSaver
 *
 * Creates a LoaderSaver object setting the initial path for the next opened dialog.
 *
 * @param initialPath: default: "."
 */
LoaderSaver::LoaderSaver(const std::string &initialPath) : actualPath(initialPath) {}

/**
 * @brief LoaderSaver::addSupportedExtension
 *
 * Adds a supported extension to the LoaderSaver.
 * Allows to open/save files of the given extension.
 *
 * Example:\n
 * \code{.cpp}
 * ls.addSupportedExtension("txt");
 * \endcode
 * @param extension: a string containing the extension, without dot.
 */
void LoaderSaver::addSupportedExtension(const std::string &extension) {
    supportedExtensions.push_back(extension);
}

/**
 * @brief LoaderSaver::resetSupportedExtension
 *
 * Removes all previously added extensions.
 */
void LoaderSaver::resetSupportedExtension() {
    supportedExtensions.clear();
}

/**
 * @brief LoaderSaver::setActualPath
 *
 * Modifies the actual path.
 *
 * @param path
 */
void LoaderSaver::setActualPath(const std::string& path) {
    actualPath = path;
}

/**
 * @brief LoaderSaver::getActualPath
 * @return the actual path.
 */
const std::string&LoaderSaver::getActualPath() const {
    return actualPath;
}

/**
 * @brief LoaderSaver::loadDialog
 *
 * Opens a Load dialog, returns the path to the selected file.
 *
 * @param windowName
 * @return
 */
std::string LoaderSaver::loadDialog(const std::string& windowName) {
    QString selectedFilter;
    QString filename = QFileDialog::getOpenFileName(nullptr,
                       QString::fromStdString(windowName),
                       QString::fromStdString(actualPath),
                       QString::fromStdString(listToExtensions(true)), &selectedFilter);

    if (!filename.isEmpty()){
        std::string path, name;
        separateFilenameFromPath(filename.toStdString(), path, name);
        actualPath = path;
    }
    return filename.toStdString();
}

/**
 * @brief LoaderSaver::saveDialog
 *
 * Opens a Save dialog, returns the path of the file to save and saves in "selectedExtension" the extension
 * of the file to save.
 *
 * @param windowName
 * @param selectedExtension
 * @return
 */
std::string LoaderSaver::saveDialog(const std::string& windowName, std::string& selectedExtension) {
    QString selectedFilter;
    selectedExtension = "";
    QString filename = QFileDialog::getSaveFileName(nullptr,
                                                    QString::fromStdString(windowName),
                                                    QString::fromStdString(actualPath),
                                                    QString::fromStdString(listToExtensions(false)), &selectedFilter);
    if (!filename.isEmpty()){
        std::string s = selectedFilter.toStdString();

        for (const std::string& tmp : supportedExtensions){
            size_t i = s.find("*(" + tmp + ")");
            if (i != std::string::npos)
                selectedExtension = tmp;
        }

        std::string path, name;
        separateFilenameFromPath(filename.toStdString(), path, name);
        actualPath = path;

    }

    return filename.toStdString();

}

/**
 * @brief LoaderSaver::directoryDialog
 *
 * Opens a dialog that allows to select a directory (no files).
 *
 * @param windowName
 * @return the path to the selected directory.
 */
std::string LoaderSaver::directoryDialog(const std::string &windowName) {
    std::string folder = "";
    QString foldername = QFileDialog::getExistingDirectory(nullptr,
                                                           QString::fromStdString(windowName),
                                                           QString::fromStdString(actualPath));
    if (!foldername.isEmpty()){
        folder = foldername.toStdString();
        actualPath = folder;
    }
    return folder;
}

std::string LoaderSaver::listToExtensions(bool allFormats) {
    std::string ext = "";
    for (const std::string& tmp : supportedExtensions){
        ext += tmp + "(*." + tmp + ");;";
    }
    ext.substr(0, ext.size()-2);
    if (allFormats){
        std::string tmp2;
        for (const std::string& tmp : supportedExtensions){
            tmp2 += "*." + tmp + " ";
        }
        tmp2.substr(0, tmp2.size()-1);

        tmp2 = "ALL(" + tmp2 + ");;";
        ext = tmp2 + ext;
    }
    return ext;
}

}

}
