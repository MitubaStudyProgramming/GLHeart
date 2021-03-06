#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderUniform.h"

#include <iostream>

using std::cout;
using std::endl;

NS_GLH_BEGIN

static ShaderProgram* g_UsingProgram = NULL;

ShaderProgram* ShaderProgram::GetUsingProgram()
{
    return g_UsingProgram;
}

ShaderProgram* ShaderProgram::QuickLoad(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{

    Shader vert(Shader::VERTEX_SHADER);
    vert.SourceFromFile(vertexShaderFilePath);
    vert.Compile();
    if (!vert.IsShaderCompiledSuccessful())
    {
        cout << vert.GetInfoLog() << endl;
        return NULL;
    }

    Shader frag(Shader::FRAGMENT_SHADER);
    frag.SourceFromFile(fragmentShaderFilePath);
    frag.Compile();
    if (!frag.IsShaderCompiledSuccessful())
    {
        cout << frag.GetInfoLog() << endl;
        return NULL;
    }

    ShaderProgram* program = new ShaderProgram();
    program->AttachShader(&vert);
    program->AttachShader(&frag);
    program->Link();

    return program;
}

ShaderProgram::ShaderProgram()
    :mId(0)
{
    mId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    for (std::map<std::string, ShaderUniform*>::iterator it = mUniforms.begin(); it != mUniforms.end(); ++it)
    {
        delete it->second;
    }
    glDeleteProgram(mId);
    if (g_UsingProgram == this) g_UsingProgram = NULL;
}

void ShaderProgram::AttachShader(Shader *shader) {
    glAttachShader(mId, shader->mId);
}

void ShaderProgram::DetachShader(Shader *shader) {
    glDetachShader(mId, shader->mId);
}

void ShaderProgram::Link() {
    glLinkProgram(mId);
}

void ShaderProgram::Use()
{
    if (g_UsingProgram == this)
        return;
    g_UsingProgram = this;
    glUseProgram(mId);
}

ShaderUniform* ShaderProgram::GetUniform(const GLchar* name)
{
    std::string key(name);
    if (mUniforms.find(key) != mUniforms.end())
    {
        return  mUniforms.at(key);
    }
    else
    {
        GLint uniformLocation = glGetUniformLocation(mId, name);
        if (uniformLocation == -1)
        {
            return NULL;
        }
        else {
            ShaderUniform *uniform = new ShaderUniform(uniformLocation);
            mUniforms[key] = uniform;
            return uniform;
        }
    }
}

NS_GLH_END