#include "mainScene.h"
#include <iostream>

#include "eCamera.h"
#include "ePointLight.h"
#include "eTime.h"
#include "eMaterial.h"
#include "eMaterialValue.h"

#define _P(_FILE_NAME_) "W:\\GLHeart\\resources\\" _FILE_NAME_

using namespace glh;
using std::cout;
using std::endl;

static GLfloat animate = 0.0f;
Mesh* gMesh = NULL;
eMaterial* gMaterial = NULL;

MainScene::MainScene(GLFWwindow *window)
    :mWindow(window)
    ,mCamera(new eCamera(window))
    ,mPointLight(NULL)
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

    mPointLight = new ePointLight(mWindow);

    gMesh = new Mesh(_P("teapot.obj"));
    gMaterial = new eMaterial();
    gMaterial->LoadTexture(_P("OM.bmp"));
    gMaterial->LoadShader(_P("phong.vert"), _P("phong.frag"));
    gMaterial->BindUniformValue("Ka", 0.2f);
    gMaterial->BindUniformValue("Kd", 0.7f);
    gMaterial->BindUniformValue("Ks", 0.4f);
    gMaterial->BindUniformValue("Shininess", new eMaterialValueFloatSlider(4.0f, 0.1f, 20.0f, 5.0f, GLFW_KEY_1, GLFW_KEY_2));
}

void MainScene::Update()
{
    eTime::Update();
    double deltaTime = eTime::GetDeltaTime();
    /// Update Camera
    mCamera->Update(deltaTime);

    mPointLight->Update(deltaTime);

    /// Update Animation
    animate += 0.1f * deltaTime;
}

void MainScene::Draw() {
    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    eCamera::Begin(mCamera);

    mPointLight->Draw();

    gMaterial->Active();

    gMaterial->GetUniform("uWorldMatrix")->SetValue(mat4());
    gMaterial->GetUniform("uViewMatrix")->SetValue(eCamera::GetCurrentCamera()->GetViewMatrix());
    gMaterial->GetUniform("uProjectionMatrix")->SetValue(eCamera::GetCurrentCamera()->GetProjectionMatrix());

    gMaterial->GetUniform("uLightPosition")->SetValue(mPointLight->GetPosition());
    gMaterial->GetUniform("uCameraPosition")->SetValue(eCamera::GetCurrentCamera()->GetPosition());

    gMesh->Draw();

    eCamera::End();
}