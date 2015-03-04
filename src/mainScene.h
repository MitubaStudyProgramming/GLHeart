#pragma once

#include "Heart.h"
#include <GLFW/glfw3.h>

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

    GLfloat mViewDistance;
    GLfloat mViewAngle;
    GLfloat mViewPitch;
    double mLastTime;
    double mLastMouseX;
    double mLastMouseY;
    GLint mLastLeftMouseButtonState;
    glm::mat4 mViewMatrix;
};
