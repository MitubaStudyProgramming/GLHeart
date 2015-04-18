#include "sceneTeapot.h"
#include "sceneBasePreincludes.h"

Mesh* gMesh = NULL;
eMaterial* gMaterial = NULL;
eMaterial* gShadowMapMaterial = NULL;

Mesh* gPlaneMesh = NULL;
eMaterial* gPlaneMaterial = NULL;

ePostprocessEffect* gPostprocessEffect = NULL;

GLuint gFBO = 0;
GLuint m_shadowMap = 0;

sceneTeapot::sceneTeapot()
    :mCamera(NULL)
    ,mPointLight(NULL)
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

    mPointLight = new ePointLight(mWindow);

    gMesh = new Mesh(_MESH("teapot"));
    gMaterial = new eMaterial();
    gMaterial->LoadTexture(_TEX("diffuse_1"));
    gMaterial->LoadShader(_SHADER("phong"));
    gMaterial->BindUniformValue("Ka", 0.2f);
    gMaterial->BindUniformValue("Kd",new eMaterialValueFloatSlider(0.7f, 0.01f, 2.0f, 0.3f, GLFW_KEY_5, GLFW_KEY_6));
    gMaterial->BindUniformValue("Ks", new eMaterialValueFloatSlider(1.0f, 0.01f, 2.0f, 0.3f, GLFW_KEY_3, GLFW_KEY_4));
    gMaterial->BindUniformValue("Shininess", new eMaterialValueFloatSlider(2.5f, 0.1f, 20.0f, 2.0f, GLFW_KEY_1, GLFW_KEY_2));

    gShadowMapMaterial = new eMaterial();
    gShadowMapMaterial->LoadTexture(_TEX("diffuse_1"));
    gShadowMapMaterial->LoadShader(_SHADER("shadow_map"));

    gPlaneMesh = new Mesh(_MESH("plane"));
    gPlaneMaterial = new eMaterial();
    gPlaneMaterial->LoadTexture(_TEX("diffuse_2"));
    gPlaneMaterial->LoadShader(_SHADER("simple"));

    glGenTextures(1, &m_shadowMap);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 768, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glGenFramebuffers(1, &gFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, gFBO);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        return;
    }

    gPostprocessEffect = new ePostprocessEffect();
    gPostprocessEffect->Load(_P("shader\\shadow_map.frag"));
}

void sceneTeapot::Update()
{
    eTime::Update();
    double deltaTime = eTime::GetDeltaTime();
    /// Update Camera
    mCamera->Update(deltaTime);

    mPointLight->Update(deltaTime);
}

void sceneTeapot::Draw() {
    // shadow map pass
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gFBO);
    Misc::Clear((ClearBit)(CLEAR_DEPTH));

    gShadowMapMaterial->Active();
    mat4 _1p = glm::perspective(20.0f, 1024.0f/768.0f, 1.0f, 50.0f);
    mat4 _1v = glm::lookAt(mPointLight->GetPosition(), vec3(), vec3(0, 1, 0));
    mat4 _1w = mat4();
    gShadowMapMaterial->GetUniform("gWVP")->SetValue(_1p * _1v * _1w);
    gMesh->Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    eCamera::Begin(mCamera);

    //mPointLight->Draw();
    /*
    gMaterial->Active();

    gMaterial->GetUniform("uWorldMatrix")->SetValue(mat4());
    gMaterial->GetUniform("uViewMatrix")->SetValue(eCamera::GetCurrentCamera()->GetViewMatrix());
    gMaterial->GetUniform("uProjectionMatrix")->SetValue(eCamera::GetCurrentCamera()->GetProjectionMatrix());

    gMaterial->GetUniform("uLightPosition")->SetValue(mPointLight->GetPosition());
    gMaterial->GetUniform("uCameraPosition")->SetValue(eCamera::GetCurrentCamera()->GetPosition());

    gMesh->Draw();

    gPlaneMaterial->Active();
    gPlaneMaterial->GetUniform("uWorldMatrix")->SetValue(glm::translate(mat4(), vec3(0, -1, 0)));
    gPlaneMaterial->GetUniform("uViewMatrix")->SetValue(eCamera::GetCurrentCamera()->GetViewMatrix());
    gPlaneMaterial->GetUniform("uProjectionMatrix")->SetValue(eCamera::GetCurrentCamera()->GetProjectionMatrix());
    gPlaneMesh->Draw();
    */

    eCamera::End();

    // render pass
    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    gPostprocessEffect->Prepare();

    Texture::Active(Texture::TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);

    gPostprocessEffect->Draw();
}