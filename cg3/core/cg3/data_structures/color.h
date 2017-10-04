#ifndef CG3_COLOR_H
#define CG3_COLOR_H

#ifdef QT_GUI_LIB

#include <QColor>

namespace cg3 {

typedef QColor Color;

}

bool operator <(const QColor &c1, const QColor &c2);


#else

#include "../io/serialize.h"

namespace cg3 {

class Color : SerializableObject {
    public:
        Color();
        Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
        int red() const;
        int green() const;
        int blue() const;
        int alpha() const;
        float redF() const;
        float greenF() const;
        float blueF() const;
        float alphaF() const;
        //toimplement
        int hsvHue() const;
        int hsvSaturation() const;
        float hsvHueF() const;
        float hsvSaturationF() const;
        void setAlpha(unsigned char alpha);
        void setRed(unsigned char red);
        void setGreen(unsigned char green);
        void setBlue(unsigned char blue);
        void setRgb(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
        void setHsv(unsigned char h, unsigned char s, unsigned char v, unsigned char alpha = 255);
        void setAlphaF(float alpha);
        void setRedF(float red);
        void setGreenF(float green);
        void setBlueF(float blue);
        void setRgbF(float red, float green, float blue, float alpha = 1.0);
        void setHsvF(float hf, float sf, float vf, float alpha = 1.0);

        bool operator == (const Color& otherColor)       const;
        bool operator != (const Color& otherColor)       const;
        bool operator < (const Color& otherColor)       const;

        // SerializableObject interface
        void serialize(std::ofstream& binaryFile) const;
        bool deserialize(std::ifstream& binaryFile);

    protected:
        int r, g, b;
        int a;


};

}

#endif

#include "color.ipp"

#endif // CG3_COLOR_H
