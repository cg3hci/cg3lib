/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_LOADERSAVER_H
#define CG3_LOADERSAVER_H

#include <string>
#include <list>
#include <memory>

namespace cg3 {

namespace viewer {

class LoaderSaver
{
public:
    LoaderSaver(const std::string& initialPath = ".");

    void addSupportedExtension(const std::string& extension);
    template <typename... Args>
    void addSupportedExtension(const std::string& ext1, Args... args);
    void resetSupportedExtension();

    void setActualPath(const std::string& path);
    const std::string& getActualPath() const;

    std::string loadDialog(const std::string &windowName = "Load File", std::string &selectedExtension = * std::unique_ptr<std::string>(new std::string("")), bool allFormats = true);
    std::string saveDialog(const std::string& windowName = "Save File", std::string &selectedExtension = * std::unique_ptr<std::string>(new std::string("")) );
    std::string directoryDialog(const std::string& windowName = "Choose Directory");

private:
    std::string actualPath;
    std::list<std::string> supportedExtensions;

    std::string listToExtensions(bool allFormats);
};

template<typename... Args>
void LoaderSaver::addSupportedExtension(const std::string &ext1, Args... args) {
    addSupportedExtension(ext1);
    addSupportedExtension(args...);
}
}

}

#endif // CG3_LOADERSAVER_H
