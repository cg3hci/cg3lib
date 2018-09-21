/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_TEXTURE_H
#define CG3_TEXTURE_H

#include <string>
#include <cg3/viewer/glcanvas.h>
#include <QImage>


namespace cg3 {
namespace opengl {

class Texture
{
public:
    Texture(const std::string& filename);
    virtual ~Texture();

    void bind(unsigned int unit = 0) const;
    void unbind() const;

private:
    GLuint texture;
    QImage img;
};

} //namespace cg3::opengl
} //namespace cg3

#endif // CG3_TEXTURE_H
