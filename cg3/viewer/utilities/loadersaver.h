#ifndef LOADERSAVER_H
#define LOADERSAVER_H

#include <string>
#include <list>
#include <memory>

namespace cg3 {

namespace Viewer {

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

#endif // LOADERSAVER_H
