#pragma once

#include "Heart.h"

class MainScene
{
public:
    void Init();
    void Update();
    void Draw();

private:
    glh::Buffer* mVertexBuffer;
    glh::Buffer* mIndexBuffer;
    glh::ShaderProgram* mProgram;
};
