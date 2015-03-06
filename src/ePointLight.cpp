#include "ePointLight.h"
#include "eCamera.h"
#include <glm/gtc/matrix_transform.hpp>

#define _P(_FILE_NAME_) "W:\\GLHeart\\resources\\" _FILE_NAME_

using namespace glh;

ePointLight::ePointLight(GLFWwindow* w)
    :mWindow(w)
    ,mMesh(NULL)
    ,mProgram(NULL)
{
    mMesh = new Mesh(_P("pointLight.obj"));
    mProgram = ShaderProgram::QuickLoad(_P("pointLight.vert"), _P("pointLight.frag"));
    mPosition = glh::vec3(2.0f, 2.0f, 1.2f);
}

ePointLight::~ePointLight()
{
    if (mMesh != NULL) delete mMesh;
    if (mProgram != NULL) delete mProgram;
}

void ePointLight::Update(double deltaTime)
{
    double move_distance = deltaTime * 4;
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        mPosition.x += move_distance;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        mPosition.x -= move_distance;
    }

    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        mPosition.z += move_distance;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        mPosition.z -= move_distance;
    }

    if (glfwGetKey(mWindow, GLFW_KEY_R) == GLFW_PRESS)
    {
        mPosition.y += move_distance;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_F) == GLFW_PRESS)
    {
        mPosition.y -= move_distance;
    }
}

void ePointLight::Draw()
{
    if (mMesh != NULL)
    {
        if (mProgram != NULL)
        {
            mProgram->Use();

            float s = 0.2f;
            mat4 worldMatrix = glm::translate(mat4(), mPosition) * glm::scale(mat4(), vec3(s,s,s));
            mat4 viewMatrix = eCamera::GetCurrentCamera()->GetViewMatrix();
            mat4 projectionMatrix = eCamera::GetCurrentCamera()->GetProjectionMatrix();
            mProgram->GetUniform("uMVP")->SetValue(projectionMatrix * viewMatrix * worldMatrix);
        }
        mMesh->Draw();
    }
}

glh::vec3 ePointLight::GetPosition() {
    return mPosition;
}
