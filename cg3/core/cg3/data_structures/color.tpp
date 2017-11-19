#include "color.h"

#ifdef QT_GUI_LIB

inline bool operator <(const QColor &c1, const QColor &c2){
    if (c1.red() < c2.red()) return true;
    if (c1.red() > c2.red()) return false;
    if (c1.green() < c2.green()) return true;
    if (c1.green() > c2.green()) return false;
    if (c1.blue() < c2.blue()) return true;
    if (c1.blue() > c2.blue()) return false;
    if (c1.alpha() < c2.alpha()) return true;
    return false;
}

#else

namespace cg3 {

inline Color::Color() : r(0), g(0), b(0), a(0){
}

inline Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : r(red), g(green), b(blue), a(alpha){
}

inline int Color::red() const {
    return r;
}

inline int Color::green() const {
    return g;
}

inline int Color::blue() const {
    return b;
}

inline int Color::alpha() const {
    return a;
}

inline float Color::redF() const {
    return (float)r/255;
}

inline float Color::greenF() const {
    return (float)g/255;
}

inline float Color::blueF() const {
    return (float)b/255;
}

inline float Color::alphaF() const {
    return (float)a/255;
}

inline int Color::hsvHue() const {
    unsigned char rgbMin, rgbMax;
    unsigned char h;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    if (rgbMax == 0) {
        return 0;
    }

    if (255 * long(rgbMax - rgbMin) / rgbMax == 0) {
        return 0;
    }

    if (rgbMax == r)
        h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    else if (rgbMax == g)
        h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    else
        h = 171 + 43 * (r - g) / (rgbMax - rgbMin);

    return h;
}

inline int Color::hsvSaturation() const {
    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    if (rgbMax == 0) {
        return 0;
    }

    return 255 * long(rgbMax - rgbMin) / rgbMax;
}

inline float Color::hsvHueF() const {
    return (float)hsvHue() / 255;
}

inline float Color::hsvSaturationF() const {
    return (float)hsvSaturation() / 255;
}

inline void Color::setAlpha(unsigned char alpha) {
    a = alpha;
}

inline void Color::setRed(unsigned char red) {
    r = red;
}

inline void Color::setGreen(unsigned char green) {
    g = green;
}

inline void Color::setBlue(unsigned char blue) {
    b = blue;
}

inline void Color::setRgb(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

inline void Color::setHsv(unsigned char h, unsigned char s, unsigned char v, unsigned char alpha) {
    a= alpha;
    if (s == 0) {
        r = v;
        g = v;
        b = v;
    }
    else {
        unsigned char region, remainder, p, q, t;
        region = h / 43;
        remainder = (h - (region * 43)) * 6;

        p = (v * (255 - s)) >> 8;
        q = (v * (255 - ((s * remainder) >> 8))) >> 8;
        t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

        switch (region) {
            case 0:
                r = v; g = t; b = p;
                break;
            case 1:
                r = q; g = v; b = p;
                break;
            case 2:
                r = p; g = v; b = t;
                break;
            case 3:
                r = p; g = q; b = v;
                break;
            case 4:
                r = t; g = p; b = v;
                break;
            default:
                r = v; g = p; b = q;
                break;
        }

    }
}

inline void Color::setAlphaF(float alpha) {
    a = (unsigned char)(alpha*255);
}

inline void Color::setRedF(float red) {
    r = (unsigned char)(red*255);
}

inline void Color::setGreenF(float green) {
    g = (unsigned char)(green*255);
}

inline void Color::setBlueF(float blue) {
    b = (unsigned char)(blue*255);
}

inline void Color::setRgbF(float red, float green, float blue, float alpha) {
    a = (unsigned char)(alpha*255);
    r = (unsigned char)(red*255);
    g = (unsigned char)(green*255);
    b = (unsigned char)(blue*255);
}

inline void Color::setHsvF(float hf, float sf, float vf, float alpha) {
    setHsv(hf*255, sf*255, vf*255, alpha*255);
}

inline bool Color::operator ==(const Color& otherColor) const {
    return (r == otherColor.r && g == otherColor.g && b == otherColor.b && a == otherColor.a);
}

inline bool Color::operator !=(const Color& otherColor) const {
    return !(*this == otherColor);
}

inline bool Color::operator <(const Color& otherColor) const {
    if (r < otherColor.r) return true;
    if (r > otherColor.r) return false;
    if (g < otherColor.g) return true;
    if (g > otherColor.g) return false;
    if (b < otherColor.b) return true;
    if (b > otherColor.b) return false;
    if (a < otherColor.a) return true;
    return false;
}

inline void Color::serialize(std::ofstream& binaryFile) const {
    SerializerOld::serialize(r, binaryFile);
    SerializerOld::serialize(g, binaryFile);
    SerializerOld::serialize(b, binaryFile);
    SerializerOld::serialize(a, binaryFile);
}

inline bool Color::deserialize(std::ifstream& binaryFile) {
    int red, green, blue, alpha;
    if (SerializerOld::deserialize(red, binaryFile) &&
        SerializerOld::deserialize(green, binaryFile) &&
        SerializerOld::deserialize(blue, binaryFile) &&
        SerializerOld::deserialize(alpha, binaryFile)){

        r = red; g = green; b = blue; a = alpha;
        return true;
    }
    else
        return false;
}

inline void Color::serializeOld(std::ofstream& binaryFile) const {
    Serializer::serializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

inline void Color::deserializeOld(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

}
#endif
