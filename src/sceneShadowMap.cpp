//
// Created by ck01- on 2015/4/18.
//

#include "sceneShadowMap.h"
#include "sceneBasePreincludes.h"

static Mesh* gMesh = NULL;
static ePostprocessEffect* gPostprocessEffect = NULL;
static eMaterial* gShadowMapMaterial = NULL;
static ePointLight* sPointLight;

static GLuint gFBO = 0;
static GLuint m_shadowMap = 0;

void sceneShadowMap::Init() {
    Misc::SetClearColorValue(0.0f, 0.5f, 0.5f, 1.0f);
    RenderStates::Depth::SetEnable(GL_TRUE);

    sPointLight = new ePointLight(mWindow);
    gMesh = new Mesh(_MESH("teapot"));

    gShadowMapMaterial = new eMaterial();
    gShadowMapMaterial->LoadTexture(_TEX("diffuse_1"));
    gShadowMapMaterial->LoadShader(_SHADER("shadow_map"));

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

void sceneShadowMap::Update() {
}

void sceneShadowMap::Draw() {
    // shadow map pass
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gFBO);
    Misc::Clear((ClearBit)(CLEAR_DEPTH));

    gShadowMapMaterial->Active();
    mat4 _1p = glm::perspective(20.0f, 1024.0f/768.0f, 1.0f, 50.0f);
    mat4 _1v = glm::lookAt(sPointLight->GetPosition(), vec3(), vec3(0, 1, 0));
    mat4 _1w = mat4();
    gShadowMapMaterial->GetUniform("gWVP")->SetValue(_1p * _1v * _1w);
    gMesh->Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // render pass
    Misc::Clear((ClearBit)(CLEAR_COLOR|CLEAR_DEPTH));

    gPostprocessEffect->Prepare();

    Texture::Active(Texture::TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);

    gPostprocessEffect->Draw();
}
