#include "mainScene.h"
#include <iostream>

using namespace glh;
using std::cout;
using std::endl;

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
};

void MainScene::Init()
{
    string vendor = Misc::GetVendor();
    string renderer = Misc::GetRenderer();
    string version = Misc::GetVersion();
    string shaderversion = Misc::GetShadingLanguageVersion();
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
}

void MainScene::Update() {

}

void MainScene::Draw() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    mProgram->Use();

    glEnableVertexAttribArray(0);

    mBuffer->Bind(Buffer::ARRAY_BUFFER);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
}