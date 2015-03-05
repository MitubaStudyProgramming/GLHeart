#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class ShaderUniform
{
private:
    ShaderUniform(GLuint location);
    ~ShaderUniform();

public:
    void SetValue(GLfloat value);
    void SetValue(const vec2& value);
    void SetValue(const vec3& value);
    void SetValue(const vec4& value);
    void SetValue(const mat4& value);

private:
    GLuint mLocation;

    friend class ShaderProgram;
};

NS_GLH_END