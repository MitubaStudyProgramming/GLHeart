#include "ePostprocessEffect.h"
#include <iostream>

#define _P(_FILE_NAME_) "W:\\GLHeart\\resources\\" _FILE_NAME_

using namespace glh;
using std::cout;
using std::endl;

ePostprocessEffect::ePostprocessEffect()
    :mProgram(NULL)
    ,mQuadMesh(NULL)
{

    std::vector<vec3> vertices;
    vertices.push_back(vec3(-1, -1, 0));
    vertices.push_back(vec3(-1, 1, 0));
    vertices.push_back(vec3(1, -1, 0));
    vertices.push_back(vec3(1, 1, 0));
    std::vector<vec2> uvs;
    uvs.push_back(vec2(0, 0));
    uvs.push_back(vec2(0, 1));
    uvs.push_back(vec2(1, 0));
    uvs.push_back(vec2(1, 1));
    std::vector<vec3> normals;
    normals.push_back(vec3(0, 0, 1));
    normals.push_back(vec3(0, 0, 1));
    normals.push_back(vec3(0, 0, 1));
    normals.push_back(vec3(0, 0, 1));
    std::vector<GLuint> indices;
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(1);
    mQuadMesh = new Mesh(vertices, uvs, normals, indices);

}

ePostprocessEffect::~ePostprocessEffect() {
    delete mProgram;
}

void ePostprocessEffect::Load(const char *fragmentShaderFilePath) {
    Shader vert(Shader::VERTEX_SHADER);
    vert.SourceFromFile(_P("shader\\postprocess.vert"));
    vert.Compile();
    if (!vert.IsShaderCompiledSuccessful())
    {
        cout << vert.GetInfoLog() << endl;
        return ;
    }
    Shader frag(Shader::FRAGMENT_SHADER);
    frag.SourceFromFile(fragmentShaderFilePath);
    frag.Compile();
    if (!frag.IsShaderCompiledSuccessful())
    {
        cout << frag.GetInfoLog() << endl;
        return ;
    }
    mProgram = new ShaderProgram();
    mProgram->AttachShader(&vert);
    mProgram->AttachShader(&frag);
    mProgram->Link();
}

void ePostprocessEffect::Prepare() {
    mProgram->Use();
}

void ePostprocessEffect::Draw() {
    mQuadMesh->Draw();
}
