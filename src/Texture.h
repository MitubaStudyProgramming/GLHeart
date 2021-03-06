#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Texture
{
public:
    enum Target
    {
        TEXTURE_1D = GL_TEXTURE_1D,
        TEXTURE_2D = GL_TEXTURE_2D,
        TEXTURE_3D = GL_TEXTURE_3D,
        TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
        TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
        TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
        TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
        TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
        TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
        TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
        TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
    };

    enum SamplerIndex
    {
        TEXTURE0 = GL_TEXTURE0,
        TEXTURE1 = GL_TEXTURE1,
        TEXTURE2 = GL_TEXTURE2,
        TEXTURE3 = GL_TEXTURE3,
        TEXTURE4 = GL_TEXTURE4,
        TEXTURE5 = GL_TEXTURE5,
        TEXTURE6 = GL_TEXTURE6,
        TEXTURE7 = GL_TEXTURE7,
        TEXTURE8 = GL_TEXTURE8,
        TEXTURE9 = GL_TEXTURE9,
        TEXTURE10 = GL_TEXTURE10,
        TEXTURE11 = GL_TEXTURE11,
        TEXTURE12 = GL_TEXTURE12,
        TEXTURE13 = GL_TEXTURE13,
        TEXTURE14 = GL_TEXTURE14,
        TEXTURE15 = GL_TEXTURE15,
        TEXTURE16 = GL_TEXTURE16,
        TEXTURE17 = GL_TEXTURE17,
        TEXTURE18 = GL_TEXTURE18,
        TEXTURE19 = GL_TEXTURE19,
        TEXTURE20 = GL_TEXTURE20,
        TEXTURE21 = GL_TEXTURE21,
        TEXTURE22 = GL_TEXTURE22,
        TEXTURE23 = GL_TEXTURE23,
        TEXTURE24 = GL_TEXTURE24,
        TEXTURE25 = GL_TEXTURE25,
        TEXTURE26 = GL_TEXTURE26,
        TEXTURE27 = GL_TEXTURE27,
        TEXTURE28 = GL_TEXTURE28,
        TEXTURE29 = GL_TEXTURE29,
        TEXTURE30 = GL_TEXTURE30,
        TEXTURE31 = GL_TEXTURE31,
    };

    static GLint GetMaxCombinedTextureImageUnits();
    static void Active(SamplerIndex index);

public:
    Texture();
    ~Texture();

    void LoadFile(const GLchar* filePath);

    void Bind(Target target);

private:
    GLuint mTextureId;

    friend class Framebuffer;
};

NS_GLH_END