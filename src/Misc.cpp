#include "Misc.h"

NS_GLH_BEGIN

namespace Misc
{
    ErrorCode GetError() {
        return (ErrorCode)glGetError();
    }

    string GetVendor()
    {
        return (const char*)glGetString(GL_VENDOR);
    }
    string GetRenderer()
    {
        return (const char*)glGetString(GL_RENDERER);
    }
    string GetVersion()
    {
        return (const char*)glGetString(GL_VERSION);
    }
    string GetShadingLanguageVersion()
    {
        return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    }

    string GetExtensions(GLuint index)
    {
        return (const char*)glGetStringi(GL_EXTENSIONS, index);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

NS_GLH_END