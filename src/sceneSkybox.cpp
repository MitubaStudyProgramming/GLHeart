//
// Created by ck01- on 2015/4/18.
//

#include "sceneSkybox.h"
#include "sceneBasePreincludes.h"
#include "eCubemapTexture.h"

#define _CUBEMAP(_NAME_) _TEX(_NAME_ "_1"), _TEX(_NAME_ "_2"), _TEX(_NAME_ "_3"), _TEX(_NAME_ "_4"), _TEX(_NAME_ "_5"), _TEX(_NAME_ "_6")

static Mesh* gMesh = NULL;
static eMaterial* gMaterial = NULL;
static Mesh* sSkyboxMesh = NULL;
static ShaderProgram* sSkyboxProgram = NULL;
static eCubemapTexture* sCubemapTexture = NULL;
static ePointLight* sPointLight;

static eCamera* mCamera;

void sceneSkybox::Init() {

    mCamera = new eCamera(mWindow);

    Misc::SetClearColorValue(0.0f, 0.5f, 0.5f, 1.0f);
    RenderStates::Depth::SetEnable(GL_TRUE);

    std::string vendor = Misc::GetVendor();
    std::string renderer = Misc::GetRenderer();
    std::string version = Misc::GetVersion();
    std::string shaderversion = Misc::GetShadingLanguageVersion();
    cout << vendor << endl << renderer << endl << version << endl << shaderversion << endl;

    sPointLight = new ePointLight(mWindow);

    gMesh = new Mesh(_MESH("teapot"));
    gMaterial = new eMaterial();
    gMaterial->LoadTexture(_TEX("diffuse_1"));
    gMaterial->LoadShader(_SHADER("phong"));
    gMaterial->BindUniformValue("Ka", 0.2f);
    gMaterial->BindUniformValue("Kd",new eMaterialValueFloatSlider(0.7f, 0.01f, 2.0f, 0.3f, GLFW_KEY_5, GLFW_KEY_6));
    gMaterial->BindUniformValue("Ks", new eMaterialValueFloatSlider(1.0f, 0.01f, 2.0f, 0.3f, GLFW_KEY_3, GLFW_KEY_4));
    gMaterial->BindUniformValue("Shininess", new eMaterialValueFloatSlider(2.5f, 0.1f, 20.0f, 2.0f, GLFW_KEY_1, GLFW_KEY_2));

    // skybox begin
    sSkyboxMesh = new Mesh(_MESH("cube"));
    sSkyboxProgram = ShaderProgram::QuickLoad(_SHADER("skybox"));
    sCubemapTexture = new eCubemapTexture();
    sCubemapTexture->Load(_CUBEMAP("snow"));
    // skybox end
}

void sceneSkybox::Update() {

    eTime::Update();
    double deltaTime = eTime::GetDeltaTime();
    /// Update Camera
    mCamera->Update(deltaTime);

    sPointLight->Update(deltaTime);
}

void sceneSkybox::Draw() {

    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    eCamera::Begin(mCamera);

    sPointLight->Draw();

    gMaterial->Active();

    gMaterial->GetUniform("uWorldMatrix")->SetValue(mat4());
    gMaterial->GetUniform("uViewMatrix")->SetValue(eCamera::GetCurrentCamera()->GetViewMatrix());
    gMaterial->GetUniform("uProjectionMatrix")->SetValue(eCamera::GetCurrentCamera()->GetProjectionMatrix());

    gMaterial->GetUniform("uLightPosition")->SetValue(sPointLight->GetPosition());
    gMaterial->GetUniform("uCameraPosition")->SetValue(eCamera::GetCurrentCamera()->GetPosition());

    gMesh->Draw();

    // skybox begin
    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    mat4 _1p = eCamera::GetCurrentCamera()->GetProjectionMatrix();
    mat4 _1v = eCamera::GetCurrentCamera()->GetViewMatrix();
    mat4 _1w = glm::translate(mat4(), eCamera::GetCurrentCamera()->GetPosition()) ;
    sSkyboxProgram->Use();
    sSkyboxProgram->GetUniform("uWVP")->SetValue(_1p * _1v * _1w);

    Texture::Active(Texture::TEXTURE0);
    sCubemapTexture->Bind();

    sSkyboxMesh->Draw();

    glCullFace(OldCullFaceMode);
    glDepthFunc(OldDepthFuncMode);
    // skybox end

    eCamera::End();
}
