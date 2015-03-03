#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

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

    ShaderUniform* GetUniform(const GLchar* name);

private:
    GLuint mId;
    std::map<std::string, ShaderUniform*> mUniforms;
};

NS_GLH_END