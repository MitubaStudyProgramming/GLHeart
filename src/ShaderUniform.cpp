#include "ShaderUniform.h"

NS_GLH_BEGIN

ShaderUniform::ShaderUniform(GLuint location)
    :mLocation(location)
{

}

ShaderUniform::~ShaderUniform()
{

}

void ShaderUniform::SetValue(GLfloat value) {
    glUniform1f(mLocation, value);
}

void ShaderUniform::SetValue(const vec2& value) {
    glUniform2f(mLocation, value[0], value[1]);
}

void ShaderUniform::SetValue(const vec3& value) {
    glUniform3f(mLocation, value[0], value[1], value[2]);
}

void ShaderUniform::SetValue(const vec4& value) {
    glUniform4f(mLocation, value[0], value[1], value[2], value[3]);
}

void ShaderUniform::SetValue(const mat4& value) {
    glUniformMatrix4fv(mLocation, 1, GL_FALSE, &value[0][0]);
}

NS_GLH_END