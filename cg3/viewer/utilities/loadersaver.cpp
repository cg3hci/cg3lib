/**
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

LoaderSaver::LoaderSaver(const std::string &initialPath) : actualPath(initialPath) {}

void LoaderSaver::addSupportedExtension(const std::string &extension) {
    supportedExtensions.push_back(extension);
}

void LoaderSaver::resetSupportedExtension() {
    supportedExtensions.clear();
}

void LoaderSaver::setActualPath(const std::string& path) {
    actualPath = path;
}

const std::string&LoaderSaver::getActualPath() const {
    return actualPath;
}

std::string LoaderSaver::loadDialog(const std::string& windowName, std::string& selectedExtension, bool allFormats) {
    QString selectedFilter;
    QString filename = QFileDialog::getOpenFileName(nullptr,
                       QString::fromStdString(windowName),
                       QString::fromStdString(actualPath),
                       QString::fromStdString(listToExtensions(allFormats)), &selectedFilter);

    if (!filename.isEmpty()){
        std::string s = selectedFilter.toStdString();

        for (const std::string& tmp : supportedExtensions){
            size_t i = s.find("(*." + tmp + ")");
            if (i != std::string::npos)
                selectedExtension = tmp;
        }
        if (selectedExtension == "")
            selectedExtension = "all";

        std::string path, name;
        separateFilenameFromPath(filename.toStdString(), path, name);
        actualPath = path;
    }
    return filename.toStdString();
}

std::string LoaderSaver::saveDialog(const std::string& windowName, std::string& selectedExtension) {
    QString selectedFilter;
    selectedExtension = "";
    QString filename = QFileDialog::getSaveFileName(nullptr,
                                                    QString::fromStdString(windowName),
                                                    QString::fromStdString(actualPath),
                                                    QString::fromStdString(listToExtensions(false)), &selectedFilter);
    if (!filename.isEmpty()){
        std::string s = selectedFilter.toStdString();
        if (s.find("ALL") != std::string::npos)
            selectedExtension = "all";
        else {
            for (const std::string& tmp : supportedExtensions){
                size_t i = s.find("*(" + tmp + ")");
                if (i != std::string::npos)
                    selectedExtension = tmp;
            }
        }

        std::string path, name;
        separateFilenameFromPath(filename.toStdString(), path, name);
        actualPath = path;

    }

    return filename.toStdString();

}

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
