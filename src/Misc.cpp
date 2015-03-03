#include "Misc.h"

NS_GLH_BEGIN

namespace Misc
{
    ErrorCode GetError() {
        return (ErrorCode)glGetError();
    }

    std::string GetVendor()
    {
        return (const char*)glGetString(GL_VENDOR);
    }
    std::string GetRenderer()
    {
        return (const char*)glGetString(GL_RENDERER);
    }
    std::string GetVersion()
    {
        return (const char*)glGetString(GL_VERSION);
    }
    std::string GetShadingLanguageVersion()
    {
        return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    }

    std::string GetExtensions(GLuint index)
    {
        return (const char*)glGetStringi(GL_EXTENSIONS, index);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

NS_GLH_END