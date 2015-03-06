#pragma once

#include "ePredefine.h"

class eMaterialValue;

class eMaterial
{
public:
    eMaterial();
    ~eMaterial();

    void LoadShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
    glh::ShaderUniform* GetUniform(const char* name);

    void BindUniformValue(const char* name, eMaterialValue* value);
    void BindUniformValue(const char* name, GLfloat value);

    void LoadTexture(const char* filePath);

    void Active();

private:
    glh::ShaderProgram* mProgram;
    glh::Texture* mTexture;
    std::vector<eMaterialValue*> mMaterialValues;
};