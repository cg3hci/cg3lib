/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#ifndef CG3_SHADER_H
#define CG3_SHADER_H

#include <cg3/utilities/const.h>
#include <cg3/viewer/glcanvas.h>

namespace cg3 {
namespace opengl {

class Shader
{
public:
    Shader(const char* fileName, bool textured = false);
    Shader(const char* vertFileName, const char* fragFileName, bool textured = false);
    Shader(const std::string& fileName, bool textured = false);
    Shader(const std::string& vertFileName, const std::string &fragFileName, bool textured = false);

    void bind() const;

    void unbind() const;

    virtual ~Shader();
private:
    typedef enum {VERTEX_SHADER, FRAGMENT_SHADER} ShaderType;

    Shader(const Shader& other) {CG3_SUPPRESS_WARNING(other);}
    void operator=(const Shader& other) {CG3_SUPPRESS_WARNING(other);}
    static std::string loadShader(const std::string& fileName);
    static bool checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string &errorMessage);
    static GLuint createShader(const std::string& fullProgram, GLenum shaderType);
    void init(bool textured);

    static const int NUM_SHADERS = 2;
    GLuint program;
    GLuint shaders[NUM_SHADERS];
};

} //namespace cg3::opengl
} //namespace cg3

#endif // CG3_SHADER_H
