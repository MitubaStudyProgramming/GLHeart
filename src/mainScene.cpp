#include "mainScene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace glh;
using std::cout;
using std::endl;

struct Vertex
{
    vec3 Position;
    vec2 TexCoord;
    vec3 Normal;

    Vertex(const vec3& pos, const vec2& texCoord, const vec3& normal)
            :Position(pos), TexCoord(texCoord), Normal(normal){}
};

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
};

static GLfloat animate = 0.0f;
Mesh* gMesh = NULL;

static Vertex g_vertices[] = {
        Vertex(vec3(-1.0f, -1.0f, 0.0f)/*X*/,  vec2(0.0f, 0.0f), vec3()),
        Vertex(vec3(0.0f, -1.0f, 1.0f)/*B*/,  vec2(0.5f, 0.0f), vec3()),
        Vertex(vec3(1.0f, -1.0f, 0.0f)/*R*/,  vec2(1.0f, 0.0f), vec3()),
        Vertex(vec3(0.0f, 1.0f, 0.0f)/*G*/,  vec2(0.5f, 1.0f), vec3()),
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
    ,mViewDistance(5.0f)
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
    Misc::SetClearColorValue(0.0f, 0.5f, 0.5f, 1.0f);
    RenderStates::Depth::SetEnable(GL_TRUE);

    std::string vendor = Misc::GetVendor();
    std::string renderer = Misc::GetRenderer();
    std::string version = Misc::GetVersion();
    std::string shaderversion = Misc::GetShadingLanguageVersion();
    cout << vendor << endl << renderer << endl << version << endl << shaderversion << endl;

    mTexture = new Texture();
    mTexture->LoadFile("W:\\GLHeart\\resources\\OM.bmp");

    {//Calc Normals
        int IndexCount = 12;
        int VertexCount = 4;
        for (int i = 0; i < IndexCount; i += 3) {
            unsigned int Index0 = g_index_buffer_data[i];
            unsigned int Index1 = g_index_buffer_data[i + 1];
            unsigned int Index2 = g_index_buffer_data[i + 2];
            vec3 v1 = g_vertices[Index1].Position - g_vertices[Index0].Position;
            vec3 v2 = g_vertices[Index2].Position - g_vertices[Index0].Position;
            vec3 Normal = glm::normalize(glm::cross(v2, v1));

            g_vertices[Index0].Normal += Normal;
            g_vertices[Index1].Normal += Normal;
            g_vertices[Index2].Normal += Normal;
        }

        for (unsigned int i = 0; i < VertexCount; i++) {
            g_vertices[i].Normal = glm::normalize(g_vertices[i].Normal);
        }
//        vec3 n = g_vertices[0].Normal;
//        cout << "X " << n.x << " " << n.y << " " << n.z << endl;
//        n = g_vertices[1].Normal;
//        cout << "B " << n.x << " " << n.y << " " << n.z << endl;
//        n = g_vertices[2].Normal;
//        cout << "R " << n.x << " " << n.y << " " << n.z << endl;
//        n = g_vertices[3].Normal;
//        cout << "G " << n.x << " " << n.y << " " << n.z << endl;
    }

    mVertexBuffer = new Buffer();
    mVertexBuffer->Data(Buffer::ARRAY_BUFFER, sizeof(g_vertices), g_vertices, glh::STATIC_DRAW);

    mIndexBuffer = new Buffer();
    mIndexBuffer->Data(Buffer::ELEMENT_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, glh::STATIC_DRAW);

    gMesh = new Mesh("W:\\GLHeart\\resources\\max.obj");

    Shader* vert = new Shader(Shader::VERTEX_SHADER);
    vert->SourceFromFile("W:\\GLHeart\\resources\\phong.vert");
    vert->Compile();
    if (!vert->IsShaderCompiledSuccessful())
    {
        cout << vert->GetInfoLog() << endl;
    }

    Shader* frag = new Shader(Shader::FRAGMENT_SHADER);
    frag->SourceFromFile("W:\\GLHeart\\resources\\phong.frag");
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

    vec3 forward = vec3(0.0f, 0.0f, 1.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    quat q = glm::rotate(quat(), mViewAngle, up);
    vec3 pos_on_xz = q * forward;
    q = glm::rotate(q, mViewPitch, glm::cross(up, pos_on_xz));

    mCameraPosition = q * pos_on_xz * mViewDistance;
    mViewMatrix = glm::lookAt(mCameraPosition, vec3(), up);

    /// Update Animation
    animate += 0.1f * deltaTime;
    ///---------------------
    mLastTime = time;
}

void MainScene::Draw() {
    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    mProgram->Use();

    //mProgram->GetUniform("Ka")->SetValue(1.2f);
    //mProgram->GetUniform("Kd")->SetValue(0.6f);
    //mProgram->GetUniform("Ks")->SetValue(0.0f);
    //mProgram->GetUniform("Shininess")->SetValue(2.3f);

    //mProgram->GetUniform("uLightPosition")->SetValue(vec3(2.0f, 2.0f, 1.0f));
    //mProgram->GetUniform("uCameraPosition")->SetValue(mCameraPosition);

    mat4 projectionMatrix = glm::perspective(45.0f, 1024.0f/768.0f, 0.1f, 1000.0f);
    mProgram->GetUniform("uProjectionMatrix")->SetValue(projectionMatrix);

    mat4 translate = glm::translate(mat4(), vec3(sinf(animate) * 0.2f, 0, 0));
    mat4 rotate = glm::toMat4(quat(vec3(animate, animate * 1.5f, animate * 2)));
    GLfloat s = sinf(animate * 2) * 0.4f + 0.6f;
    mat4 scale = glm::scale(mat4(), vec3(s, s, s));
    mProgram->GetUniform("uWorldMatrix")->SetValue(mat4());//translate * rotate * scale);

    mProgram->GetUniform("uViewMatrix")->SetValue(mViewMatrix);

    Texture::Active(Texture::TEXTURE0);
    mTexture->Bind(Texture::TEXTURE_2D);

//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);
//
//    mVertexBuffer->Bind(Buffer::ARRAY_BUFFER);
//    mIndexBuffer->Bind(Buffer::ELEMENT_ARRAY_BUFFER);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
//
//    //glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//
//    glDisableVertexAttribArray(2);
//    glDisableVertexAttribArray(1);
//   glDisableVertexAttribArray(0);
   gMesh->Draw();
}