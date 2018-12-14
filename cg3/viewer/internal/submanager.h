#ifndef CG3_SUBFRAME_H
#define CG3_SUBFRAME_H

#include <QFrame>

namespace cg3 {
namespace viewer {

/**
 * @brief The SubManager class
 * A class that represent a sub
 */
class SubManager : public QFrame{
public:
    explicit SubManager(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
        QFrame(parent, f)
    {
    }
    ~SubManager() {}

    /**
     * @brief Allows to update the properties of the DrawableObject according to the properties
     * setted in the user interface.
     */
    virtual void updateObjectProperties() = 0;

    /**
     * @brief Allows to update the properties setted in the user interface according to the
     * properties of the DrawableObject.
     */
    virtual void updateManagerProperties() = 0;
};

}
}

#endif // CG3_SUBFRAME_H
