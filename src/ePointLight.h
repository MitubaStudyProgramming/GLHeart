#pragma once

#include "ePredefine.h"

class ePointLight
{
public:
    ePointLight(GLFWwindow* w);
    ~ePointLight();

    void Update(double deltaTime);
    void Draw();

    glh::vec3 GetPosition();

private:
    GLFWwindow* mWindow;
    glh::Mesh* mMesh;
    glh::ShaderProgram* mProgram;

    glh::vec3 mPosition;
};