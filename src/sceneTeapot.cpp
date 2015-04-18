#include "sceneTeapot.h"
#include "sceneBasePreincludes.h"

static Mesh* gMesh = NULL;
static eMaterial* gMaterial = NULL;

static Mesh* gPlaneMesh = NULL;
static eMaterial* gPlaneMaterial = NULL;
static ePointLight* sPointLight;

sceneTeapot::sceneTeapot()
    :mCamera(NULL)
{
}

void sceneTeapot::Init()
{
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

    gPlaneMesh = new Mesh(_MESH("plane"));
    gPlaneMaterial = new eMaterial();
    gPlaneMaterial->LoadTexture(_TEX("diffuse_2"));
    gPlaneMaterial->LoadShader(_SHADER("simple"));
}

void sceneTeapot::Update()
{
    eTime::Update();
    double deltaTime = eTime::GetDeltaTime();
    /// Update Camera
    mCamera->Update(deltaTime);

    sPointLight->Update(deltaTime);
}

void sceneTeapot::Draw() {
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

    gPlaneMaterial->Active();
    gPlaneMaterial->GetUniform("uWorldMatrix")->SetValue(glm::translate(mat4(), vec3(0, -1, 0)));
    gPlaneMaterial->GetUniform("uViewMatrix")->SetValue(eCamera::GetCurrentCamera()->GetViewMatrix());
    gPlaneMaterial->GetUniform("uProjectionMatrix")->SetValue(eCamera::GetCurrentCamera()->GetProjectionMatrix());
    gPlaneMesh->Draw();

    eCamera::End();
}