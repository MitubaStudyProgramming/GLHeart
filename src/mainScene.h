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
    glh::Texture* mTexture;

    GLfloat mViewDistance;
    GLfloat mViewAngle;
    GLfloat mViewPitch;
    double mLastTime;
    double mLastMouseX;
    double mLastMouseY;
    GLint mLastLeftMouseButtonState;
    glh::mat4 mViewMatrix;
    glh::vec3 mCameraPosition;
};
