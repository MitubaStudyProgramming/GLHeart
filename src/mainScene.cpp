#include "mainScene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace glh;
using std::cout;
using std::endl;

static GLfloat animate = 0.0f;
ShaderUniform*uWorldMatrix = NULL;
ShaderUniform* uProjectionMatrix = NULL;
ShaderUniform* uViewMatrix = NULL;

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, /*X*/ 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, /*B*/ 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, /*R*/ 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, /*G*/ 0.5f, 1.0f,
};
static const GLuint g_index_buffer_data[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2,
};

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

MainScene::MainScene(GLFWwindow *window)
    :mWindow(window)
    ,mViewDistance(2.0f)
    ,mViewAngle(0)
    ,mViewPitch(0)
    ,mLastTime(0)
    ,mLastMouseX(0)
    ,mLastMouseY(0)
    ,mLastLeftMouseButtonState(GLFW_RELEASE)
{

}

void MainScene::Init()
{
    RenderStates::Depth::SetEnable(GL_TRUE);

    std::string vendor = Misc::GetVendor();
    std::string renderer = Misc::GetRenderer();
    std::string version = Misc::GetVersion();
    std::string shaderversion = Misc::GetShadingLanguageVersion();
    cout << vendor << endl << renderer << endl << version << endl << shaderversion << endl;

    mTexture = new Texture();
    mTexture->LoadFile("W:\\GLHeart\\resources\\OM.bmp");

    mVertexBuffer = new Buffer();
    mVertexBuffer->Data(Buffer::ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, glh::STATIC_DRAW);

    mIndexBuffer = new Buffer();
    mIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, glh::STATIC_DRAW);

    Shader* vert = new Shader(Shader::VERTEX_SHADER);
    vert->SourceFromFile("W:\\GLHeart\\resources\\simple.vert");
    vert->Compile();
    if (!vert->IsShaderCompiledSuccessful())
    {
        cout << vert->GetInfoLog() << endl;
    }

    Shader* frag = new Shader(Shader::FRAGMENT_SHADER);
    frag->SourceFromFile("W:\\GLHeart\\resources\\simple.frag");
    frag->Compile();
    if (!frag->IsShaderCompiledSuccessful())
    {
        cout << frag->GetInfoLog() << endl;
    }

    mProgram = new ShaderProgram();
    mProgram->AttachShader(vert);
    mProgram->AttachShader(frag);
    mProgram->Link();

    delete vert;
    delete frag;

    uWorldMatrix = mProgram->GetUniform("uWorldMatrix");
    uProjectionMatrix = mProgram->GetUniform("uProjectionMatrix");
    uViewMatrix = mProgram->GetUniform("uViewMatrix");
}

void MainScene::Update()
{
    double time = glfwGetTime();
    double deltaTime = time - mLastTime;
    /// Update Camera
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
    if (glfwGetKey(mWindow, GLFW_KEY_MINUS) == GLFW_PRESS)
    {
        mViewDistance -= deltaTime;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_EQUAL) == GLFW_PRESS)
    {
        mViewDistance += deltaTime;
    }
    mViewDistance = clamp(mViewDistance, 0.5f, 10.0f);

    glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::quat q = glm::rotate(glm::quat(), mViewAngle, up);
    glm::vec3 pos_on_xz = q * forward;
    q = glm::rotate(q, mViewPitch, glm::cross(up, pos_on_xz));
    glm::vec3 eyePos = q * pos_on_xz * mViewDistance;

    mViewMatrix = glm::lookAt(eyePos, glm::vec3(), -up);

    /// Update Animation
    animate += 0.1f * deltaTime;
    ///---------------------
    mLastTime = time;
}

void MainScene::Draw() {
    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    mProgram->Use();

    glm::mat4 projectionMatrix = glm::perspective(30.0f, 1024.0f/768.0f, 0.1f, 1000.0f);
    uProjectionMatrix->SetValue(projectionMatrix);

    glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(sinf(animate) * 0.2f, 0, 0));
    glm::mat4 rotate = glm::toMat4(glm::quat(glm::vec3(animate, animate * 1.5f, animate * 2)));
    GLfloat s = 1;//sinf(animate * 2) * 0.4f + 0.6f;
    glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(s, s, s));
    uWorldMatrix->SetValue(glm::mat4());//translate * rotate * scale);

    uViewMatrix->SetValue(mViewMatrix);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mVertexBuffer->Bind(Buffer::ARRAY_BUFFER);
    mIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (const GLvoid*)12);

    Texture::Active(Texture::TEXTURE0);
    mTexture->Bind(Texture::TEXTURE_2D);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}