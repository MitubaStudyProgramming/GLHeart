#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

namespace Misc
{
    ErrorCode GetError();

    std::string GetVendor();
    std::string GetRenderer();
    std::string GetVersion();
    std::string GetShadingLanguageVersion();

    std::string GetExtensions(GLuint index);

    void Clear(ClearBit bits);
    void SetClearColorValue(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void SetClearDepthValue(GLclampd depth);
    void SetClearStencilValue(GLint s);
}

NS_GLH_END