#include "Shader.h"
#include <fstream>
#include <cstring>

NS_GLH_BEGIN

Shader::Shader(ShaderType type)
    :mId(0)
{
    mId = glCreateShader((GLenum)type);
}

Shader::~Shader() {
    glDeleteShader(mId);
}

void Shader::Source(GLsizei count, const GLchar* const *string, const int *length) {
    glShaderSource(mId, count, string, length);
}

void Shader::SourceFromFile(const GLchar *filePath) {
    string code;
    std::ifstream is(filePath, std::ios::in);
    if (is.is_open())
    {
        string line;
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

NS_GLH_END