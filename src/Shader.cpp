#include "Shader.h"
#include <fstream>

NS_GLH_BEGIN

Shader::Shader(ShaderType type)
    :mId(0)
{
    mId = glCreateShader((GLenum)type);
}

Shader::~Shader() {
    glDeleteShader(mId);
}

void Shader::Source(GLsizei count, const GLchar* const *text, const int *length) {
    glShaderSource(mId, count, text, length);
}

void Shader::SourceFromFile(const GLchar *filePath) {
    std::string code;
    std::ifstream is(filePath, std::ios::in);
    if (is.is_open())
    {
        std::string line;
        while (std::getline(is, line))
            code += (line + "\n");
        is.close();
    }

    const GLchar *pStrCode = code.c_str();
    Source(1, &pStrCode, NULL);
}

void Shader::Compile() {
    glCompileShader(mId);
}

Shader::ShaderType Shader::GetShaderType() const {
    GLint result;
    glGetShaderiv(mId, GL_SHADER_TYPE, &result);
    return (ShaderType)result;
}

GLboolean Shader::IsShaderDeleted() const {
    GLint result;
    glGetShaderiv(mId, GL_DELETE_STATUS, &result);
    return (GLboolean)result;
}

GLboolean Shader::IsShaderCompiledSuccessful() const {
    GLint result;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &result);
    return (GLboolean)result;
}

GLint Shader::GetShaderSourceLength() const {
    GLint result;
    glGetShaderiv(mId, GL_SHADER_SOURCE_LENGTH, &result);
    return result;
}

std::string Shader::GetInfoLog() const {
    GLint infoLength;
    glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &infoLength);
    std::string infoLog(infoLength+1, '\0');
    glGetShaderInfoLog(mId, infoLength, NULL, &infoLog[0]);
    return infoLog;
}

NS_GLH_END