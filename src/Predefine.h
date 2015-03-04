#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#define NS_GLH_BEGIN namespace glh {
#define NS_GLH_END }

NS_GLH_BEGIN

enum ErrorCode
{
    NO_ERROR = GL_NO_ERROR,
    INVALID_ENUM = GL_INVALID_ENUM,
    INVALID_VALUE = GL_INVALID_VALUE,
    INVALID_OPERATION = GL_INVALID_OPERATION,
    INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
    OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
};

enum BufferDataUsage
{
    STREAM_DRAW = GL_STREAM_DRAW,
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY,
    STATIC_DRAW = GL_STATIC_DRAW,
    STATIC_READ = GL_STATIC_READ,
    STATIC_COPY = GL_STATIC_COPY,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

class Buffer;
class Shader;
class ShaderProgram;
class ShaderUniform;
class Transform;

NS_GLH_END