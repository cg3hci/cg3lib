/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "shader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <QTextStream>

namespace cg3 {
namespace opengl {

Shader::Shader(const char *fileName, bool textured) : Shader(std::string(fileName), textured)
{
}

Shader::Shader(const char *vertFileName, const char *fragFileName, bool textured) :
    Shader(std::string(vertFileName), std::string(fragFileName), textured)
{
}

Shader::Shader(const std::string &fileName, bool textured)
{
    program = glCreateProgram();
    shaders[VERTEX_SHADER] = createShader(loadShader(fileName + ".vert"), GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = createShader(loadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

    init(textured);
}

Shader::Shader(const std::string &vertFileName, const std::string& fragFileName, bool textured)
{
    program = glCreateProgram();
    shaders[VERTEX_SHADER] = createShader(loadShader(vertFileName), GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = createShader(loadShader(fragFileName), GL_FRAGMENT_SHADER);

    init(textured);
}

void Shader::bind() const
{
    glUseProgram(program);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++){
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(program);
}

std::string Shader::loadShader(const std::string &fileName)
{
    std::string output;
    QFile file(QString::fromStdString(fileName));;
    bool ok = file.open(QIODevice::ReadOnly);
    if (ok){
        QTextStream in(&file);

        while(!in.atEnd()){
            QString line = in.readLine();
            output.append(line.toStdString() + "\n");
        }

    }
    else {
        throw std::runtime_error("Unable to load shader " + fileName);
    }
    return output;
}

bool Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string &errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {};

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE){
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        errorMessage = std::string(error);
        return true;
    }

    return false;
}

GLuint Shader::createShader(const std::string &fullProgram, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        throw std::runtime_error("Error: Shader creation failed.");


    const GLchar* shaderSourceStrings[1];
    shaderSourceStrings[0] = fullProgram.c_str();
    GLint shaderSourceStringsLength[1];

    shaderSourceStringsLength[0] = fullProgram.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
    glCompileShader(shader);

    std::string error_message;
    bool error = checkShaderError(shader, GL_COMPILE_STATUS, false, error_message);
    if (error)
        throw std::runtime_error("Error: Shader compilation failed; msg:" + error_message);

    return shader;
}

void Shader::init(bool textured)
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(program, shaders[i]);

    glBindAttribLocation(program, 0, "position");
    if (textured)
        glBindAttribLocation(program, 1, "texCoord");

    std::string error_message;
    glLinkProgram(program);
    bool error = checkShaderError(program, GL_LINK_STATUS, true, error_message);

    if (error)
        throw std::runtime_error("Error: Program linking failed; msg: " + error_message);

    glValidateProgram(program);
    error = checkShaderError(program, GL_VALIDATE_STATUS, true, error_message);

    if (error)
        throw std::runtime_error("Error: Program is invalid; msg: " + error_message);
}

} //namespace cg3::opengl
} //namespace cg3
