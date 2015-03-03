#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Shader
{
public:
    enum ShaderType
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    };
public:
    Shader(ShaderType type);
    ~Shader();

    void Source(GLsizei count, const GLchar* const* string, const int* length);
    void SourceFromFile(const GLchar* filePath);
    void Compile();

private:
    GLuint mId;

    friend class ShaderProgram;
};

NS_GLH_END