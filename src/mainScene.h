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

    eCamera* mCamera;
    ePointLight* mPointLight;
};
