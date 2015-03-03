#pragma once

#include "Heart.h"

class MainScene
{
public:
    void Init();
    void Update();
    void Draw();

private:
    glh::Buffer* mBuffer;
    glh::ShaderProgram* mProgram;
};
