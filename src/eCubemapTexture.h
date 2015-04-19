//
// Created by ck01- on 2015/4/19.
//

#ifndef GLHEART_ECUBEMAPTEXTURE_H
#define GLHEART_ECUBEMAPTEXTURE_H

#include "ePredefine.h"

class eCubemapTexture
{
public:
    eCubemapTexture();
    ~eCubemapTexture();

    void Load(
            const char* texPosXFilePath,
            const char* texNegXFilePath,
            const char* texPosYFilePath,
            const char* texNegYFilePath,
            const char* texPosZFilePath,
            const char* texNegZFilePath
    );

    void Bind();
    void Active(glh::Texture::SamplerIndex index);

private:
    GLuint mTextureId;
};


#endif //GLHEART_ECUBEMAPTEXTURE_H
