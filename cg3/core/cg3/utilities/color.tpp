/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

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

/**
 * @brief Color::Color
 * Default constructor.
 * Initializes a black color.
 */
inline Color::Color() : r(0), g(0), b(0), a(0){
}

/**
 * @brief Color::Color
 * Color constructor.
 * @param[in] red: red component
 * @param[in] green: green component
 * @param[in] blue: blue component
 * @param[in] alpha: alpha component (default 255)
 */
inline Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : r(red), g(green), b(blue), a(alpha){
}

/**
 * @brief Color::red
 * Returns the red component of this color [0-255]
 * @return red component of this color
 */
inline int Color::red() const {
    return r;
}

/**
 * @brief Color::green
 * Returns the green component of this color [0-255]
 * @return green component of this color
 */
inline int Color::green() const {
    return g;
}

/**
 * @brief Color::blue
 * Returns the blue component of this color [0-255]
 * @return blue component of this color
 */
inline int Color::blue() const {
    return b;
}

/**
 * @brief Color::alpha
 * Returns the alpha component of this color [0-255]
 * @return alpha component of this color
 */
inline int Color::alpha() const {
    return a;
}

/**
 * @brief Color::redF
 * Returns the float red component of this color [0-1]
 * @return float red component of this color
 */
inline float Color::redF() const {
    return (float)r/255;
}

/**
 * @brief Color::greenF
 * Returns the float green component of this color [0-1]
 * @return float green component of this color
 */
inline float Color::greenF() const {
    return (float)g/255;
}

/**
 * @brief Color::blueF
 * Returns the float blue component of this color [0-1]
 * @return float blue component of this color
 */
inline float Color::blueF() const {
    return (float)b/255;
}

/**
 * @brief Color::alphaF
 * Returns the float alpha component of this color [0-1]
 * @return float alpha component of this color
 */
inline float Color::alphaF() const {
    return (float)a/255;
}

/**
 * @brief Color::hsvHue
 * Returns the hue color component of this color [0-255]
 * @return hue color component of this color
 */
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

/**
 * @brief Color::hsvSaturation
 * Returns the saturation color component of this color [0-255]
 * @return saturation color component of this color
 */
inline int Color::hsvSaturation() const {
    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    if (rgbMax == 0) {
        return 0;
    }

    return 255 * long(rgbMax - rgbMin) / rgbMax;
}

/**
 * @brief Color::hsvHueF
 * Returns the float saturation color component of this color [0-1]
 * @return float saturation color component of this color
 */
inline float Color::hsvHueF() const {
    return (float)hsvHue() / 255;
}

/**
 * @brief Color::hsvSaturationF
 * Returns the float saturation color component of this color [0-1]
 * @return float saturation color component of this color
 */
inline float Color::hsvSaturationF() const {
    return (float)hsvSaturation() / 255;
}

/**
 * @brief Color::setAlpha
 * Sets the alpha of this color [0-255]
 * @param[in] alpha
 */
inline void Color::setAlpha(unsigned char alpha) {
    a = alpha;
}

/**
 * @brief Color::setRed
 * Sets the red of this color [0-255]
 * @param[in] red
 */
inline void Color::setRed(unsigned char red) {
    r = red;
}

/**
 * @brief Color::setGreen
 * Sets the green of this color [0-255]
 * @param[in] green
 */
inline void Color::setGreen(unsigned char green) {
    g = green;
}

/**
 * @brief Color::setBlue
 * Sets the blue of this color [0-255]
 * @param[in] blue
 */
inline void Color::setBlue(unsigned char blue) {
    b = blue;
}

/**
 * @brief Color::setRgb
 * Sets the RGB values of this color.
 * All the values must be in the range 0-255.
 * @param[in] red
 * @param[in] green
 * @param[in] blue
 * @param[in] alpha: default 255
 */
inline void Color::setRgb(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

/**
 * @brief Color::setHsv
 * Sets the HSV values of this color.
 * All the values must be in the range 0-255.
 * @param[in] h
 * @param[in] s
 * @param[in] v
 * @param[in] alpha: default 255
 */
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

/**
 * @brief Color::setAlphaF
 * Sets the alpha of this color [0-1]
 * @param[in] alpha
 */
inline void Color::setAlphaF(float alpha) {
    a = (unsigned char)(alpha*255);
}

/**
 * @brief Color::setRedF
 * Sets the red of this color [0-1]
 * @param[in] red
 */
inline void Color::setRedF(float red) {
    r = (unsigned char)(red*255);
}

/**
 * @brief Color::setGreenF
 * Sets the green of this color [0-1]
 * @param[in] green
 */
inline void Color::setGreenF(float green) {
    g = (unsigned char)(green*255);
}

/**
 * @brief Color::setBlueF
 * Sets the blue of this color [0-1]
 * @param[in] blue
 */
inline void Color::setBlueF(float blue) {
    b = (unsigned char)(blue*255);
}

/**
 * @brief Color::setRgbF
 * Sets the RGB values of this color.
 * All the values must be in the range 0-1.
 * @param[in] red
 * @param[in] green
 * @param[in] blue
 * @param[in] alpha: default 1
 */
inline void Color::setRgbF(float red, float green, float blue, float alpha) {
    a = (unsigned char)(alpha*255);
    r = (unsigned char)(red*255);
    g = (unsigned char)(green*255);
    b = (unsigned char)(blue*255);
}

/**
 * @brief Color::setHsvF
 * Sets the HSV values of this color.
 * All the values must be in the range 0-1.
 * @param[in] hf
 * @param[in] sf
 * @param[in] vf
 * @param[in] alpha
 */
inline void Color::setHsvF(float hf, float sf, float vf, float alpha) {
    setHsv((int)hf*255, (int)sf*255, (int)vf*255, (int)alpha*255);
}

/**
 * @brief Color::operator ==
 * Returns true if this color has the same RGB and alpha values as otherColor; otherwise returns false.
 * @param otherColor
 * @return
 */
inline bool Color::operator ==(const Color& otherColor) const {
    return (r == otherColor.r && g == otherColor.g && b == otherColor.b && a == otherColor.a);
}

/**
 * @brief Color::operator !=
 * Returns false if this color has the same RGB and alpha values as otherColor; otherwise returns true.
 * @param otherColor
 * @return
 */
inline bool Color::operator !=(const Color& otherColor) const {
    return !(*this == otherColor);
}

/**
 * @brief Color::operator <
 * Returns true if this color is less than otherColor follwing the RGBA order; otherwise returns false.
 * @param otherColor
 * @return
 */
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
    Serializer::serializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

inline void Color::deserialize(std::ifstream& binaryFile) {
    Serializer::deserializeObjectAttributes("cg3Color", binaryFile, r, g, b, a);
}

}
#endif

inline std::size_t std::hash<cg3::Color>::operator()(const cg3::Color &k) const {
    std::size_t seed = 0;
    cg3::hashCombine(seed, k.red(), k.green(), k.blue(), k.alpha());
    return seed;
}
