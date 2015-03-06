#include "eCamera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glh;

static eCamera* gCurrentCamera = NULL;
static double gScrollOffset = 0;

static void _onGLFWScroll(GLFWwindow *w, double xoffset, double yoffset)
{
    gScrollOffset += yoffset;
}

eCamera* eCamera::GetCurrentCamera()
{
    return gCurrentCamera;
}

void eCamera::Begin(eCamera *cam)
{
    gCurrentCamera = cam;
}

void eCamera::End() {
    gCurrentCamera = NULL;
}

eCamera::eCamera(GLFWwindow *w)
    :mWindow(w)
    ,mViewDistance(5.0f)
    ,mViewAngle(0)
    ,mViewPitch(0)
    ,mLastMouseX(0)
    ,mLastMouseY(0)
    ,mLastLeftMouseButtonState(GLFW_RELEASE)
{
    glfwSetScrollCallback(mWindow, _onGLFWScroll);
}

void eCamera::Update(double deltaTime)
{
    // rotate
    GLint leftMouseButtonState = glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT);
    if (leftMouseButtonState == GLFW_PRESS)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(mWindow, &mouseX, &mouseY);
        if (mLastLeftMouseButtonState != GLFW_RELEASE)
        {
            double deltaX = mouseX - mLastMouseX;
            double deltaY = mouseY - mLastMouseY;

            mViewAngle -= deltaX * 0.01f;
            mViewPitch -= deltaY * 0.01f;
        }
        mLastMouseX = mouseX;
        mLastMouseY = mouseY;
    }
    mLastLeftMouseButtonState = leftMouseButtonState;

    // scale
    mViewDistance -= gScrollOffset;
    gScrollOffset = 0;
    mViewDistance = clamp(mViewDistance, 0.5f, 50.0f);

    // calc
    vec3 forward = vec3(0.0f, 0.0f, 1.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    quat q = glm::rotate(quat(), mViewAngle, up);
    vec3 pos_on_xz = q * forward;
    q = glm::rotate(q, mViewPitch, glm::cross(up, pos_on_xz));

    mCameraPosition = q * pos_on_xz * mViewDistance;
    mViewMatrix = glm::lookAt(mCameraPosition, vec3(), up);

}

glh::vec3 eCamera::GetPosition() {
    return mCameraPosition;
}

glh::mat4 eCamera::GetViewMatrix() {
    return mViewMatrix;
}

glh::mat4 eCamera::GetProjectionMatrix() {
    return glm::perspective(45.0f, 1024.0f/768.0f, 0.1f, 1000.0f);
}