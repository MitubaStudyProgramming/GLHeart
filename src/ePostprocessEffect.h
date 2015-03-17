#pragma once

#include "ePredefine.h"


class ePostprocessEffect
{
public:
    ePostprocessEffect();
    ~ePostprocessEffect();

    void Load(const char* fragmentShaderFilePath);

    void Prepare();
    void Draw();

    glh::ShaderProgram* GetProgram() const {
        return mProgram;
    }

private:
    glh::Mesh* mQuadMesh;
    glh::ShaderProgram* mProgram;
};
