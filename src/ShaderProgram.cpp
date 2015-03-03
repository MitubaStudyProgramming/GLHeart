#include "ShaderProgram.h"
#include "Shader.h"

NS_GLH_BEGIN

static ShaderProgram* g_UsingProgram = NULL;

ShaderProgram* ShaderProgram::GetUsingProgram()
{
    return g_UsingProgram;
}

ShaderProgram::ShaderProgram()
    :mId(0)
{
    mId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
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

NS_GLH_END