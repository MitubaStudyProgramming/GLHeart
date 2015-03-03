#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

namespace Misc
{
    ErrorCode GetError();

    string GetVendor();
    string GetRenderer();
    string GetVersion();
    string GetShadingLanguageVersion();

    string GetExtensions(GLuint index);

    void Clear();
}

NS_GLH_END