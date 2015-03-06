#pragma once

#include "Heart.h"
#include <GLFW/glfw3.h>

class eCamera;
class ePointLight;

class MainScene
{
public:
    MainScene(GLFWwindow* window);

    void Init();
    void Update();
    void Draw();

private:
    GLFWwindow* mWindow;
    glh::Buffer* mVertexBuffer;
    glh::Buffer* mIndexBuffer;
    glh::ShaderProgram* mProgram;
    glh::Texture* mTexture;

    double mLastTime;
    eCamera* mCamera;
    ePointLight* mPointLight;
};
