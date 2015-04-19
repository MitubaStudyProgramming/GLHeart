//
// Created by ck01- on 2015/4/19.
//

#include "eCubemapTexture.h"

struct eCubemapTextureFaceInfo
{
    GLenum BindTarget;
    const char* FilePath;
};

eCubemapTexture::eCubemapTexture()
{
    glGenTextures(1, &mTextureId);
}

eCubemapTexture::~eCubemapTexture() {
    glDeleteTextures(1, &mTextureId);
}

void eCubemapTexture::Load(const char *texPosXFilePath, const char *texNegXFilePath, const char *texPosYFilePath,
                           const char *texNegYFilePath, const char *texPosZFilePath, const char *texNegZFilePath) {
    this->Bind();

    eCubemapTextureFaceInfo faces[6] = {
        { GL_TEXTURE_CUBE_MAP_POSITIVE_X, texPosXFilePath },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_X, texNegXFilePath },
        { GL_TEXTURE_CUBE_MAP_POSITIVE_Y, texPosYFilePath },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, texNegYFilePath },
        { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, texPosZFilePath },
        { GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, texNegZFilePath },
    };

    for(int i=0;i<6;++i)
    {
        const char* filePath = faces[i].FilePath;
// Data read from the header of the BMP file
        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int dataPos;     // Position in the file where the actual data begins
        unsigned int width, height;
        unsigned int imageSize;   // = width*height*3
// Actual RGB data
        unsigned char * data;

        // Open the file
        FILE * file = fopen(filePath, "rb");
        if (!file)
        {
            printf("Image could not be opened. (%s)\n", filePath);
            return;
        }

        if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
            printf("Not a correct BMP file. (%s)\n", filePath);
            return;
        }

        if ( header[0]!='B' || header[1]!='M' ){
            printf("Not a correct BMP file. (%s)\n", filePath);
            return;
        }

        // Read ints from the byte array
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way

        // Create a buffer
        data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
        fclose(file);

        glTexImage2D(faces[i].BindTarget, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

        delete data;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void eCubemapTexture::Bind() {
    glBindTexture(glh::Texture::TEXTURE_CUBE_MAP, mTextureId);
}

void eCubemapTexture::Active(glh::Texture::SamplerIndex index) {
    glActiveTexture((GLenum)index);
}
