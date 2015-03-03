#include "mainScene.h"
#include "ShaderUniform.h"
#include <iostream>

using namespace glh;
using std::cout;
using std::endl;

static GLfloat scale = 0.0f;
ShaderUniform* uniformScale = NULL;

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
};

void MainScene::Init()
{
    std::string vendor = Misc::GetVendor();
    std::string renderer = Misc::GetRenderer();
    std::string version = Misc::GetVersion();
    std::string shaderversion = Misc::GetShadingLanguageVersion();
    cout << vendor << endl << renderer << endl << version << endl << shaderversion << endl;

    mBuffer = new Buffer();
    mBuffer->Data(Buffer::ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, glh::STATIC_DRAW);

    Shader* vert = new Shader(Shader::VERTEX_SHADER);
    vert->SourceFromFile("W:\\GLHeart\\resources\\simple.vert");
    vert->Compile();

    Shader* frag = new Shader(Shader::FRAGMENT_SHADER);
    frag->SourceFromFile("W:\\GLHeart\\resources\\simple.frag");
    frag->Compile();

    mProgram = new ShaderProgram();
    mProgram->AttachShader(vert);
    mProgram->AttachShader(frag);
    mProgram->Link();

    delete vert;
    delete frag;

    uniformScale = mProgram->GetUniform("gScale");
}

void MainScene::Update() {
}

void MainScene::Draw() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    mProgram->Use();
    scale += 0.001f;
    uniformScale->SetValue(sinf(scale));

    glEnableVertexAttribArray(0);

    mBuffer->Bind(Buffer::ARRAY_BUFFER);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
}