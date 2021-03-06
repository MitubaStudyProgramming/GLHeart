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

enum ClearBit
{
    CLEAR_COLOR = GL_COLOR_BUFFER_BIT,
    CLEAR_DEPTH = GL_DEPTH_BUFFER_BIT,
    CLEAR_STENCIL = GL_STENCIL_BUFFER_BIT,
};

enum DepthFunc
{
    DF_NEVER = GL_NEVER,
    DF_LESS = GL_LESS,
    DF_EQUAL = GL_EQUAL,
    DF_LEQUAL = GL_LEQUAL,
    DF_GREATER = GL_GREATER,
    DF_NOTEQUAL = GL_NOTEQUAL,
    DF_GEQUAL = GL_GEQUAL,
    DF_ALWAYS = GL_ALWAYS,
};

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;
typedef glm::quat quat;

class Buffer;
class Framebuffer;
class Mesh;
class Shader;
class ShaderProgram;
class ShaderUniform;
class Technique;
class Texture;
class Transform;

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

NS_GLH_END