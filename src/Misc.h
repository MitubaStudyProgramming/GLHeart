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

    void Clear();
}

NS_GLH_END