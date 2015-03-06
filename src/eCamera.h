#pragma once

#include "ePredefine.h"

class eCamera
{
public:
    static eCamera* GetCurrentCamera();
    static void Begin(eCamera* cam);
    static void End();

public:
    eCamera(GLFWwindow* w);

    void Update(double deltaTime);

    glh::vec3 GetPosition();

    glh::mat4 GetViewMatrix();
    glh::mat4 GetProjectionMatrix();

private:
    GLFWwindow* mWindow;

    GLfloat mViewDistance;
    GLfloat mViewAngle;
    GLfloat mViewPitch;
    double mLastMouseX;
    double mLastMouseY;
    GLint mLastLeftMouseButtonState;
    glh::mat4 mViewMatrix;
    glh::vec3 mCameraPosition;
};