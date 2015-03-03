#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Shader;

class ShaderProgram
{
public:
    static ShaderProgram* GetUsingProgram();
public:
    ShaderProgram();
    ~ShaderProgram();

    void AttachShader(Shader* shader);
    void DetachShader(Shader* shader);

    void Link();
    void Use();

private:
    GLuint mId;
};

NS_GLH_END