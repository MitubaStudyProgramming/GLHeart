#include "Texture.h"

NS_GLH_BEGIN

GLint Texture::GetMaxCombinedTextureImageUnits()
{
    GLint result;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &result);
    return result;
}

Texture::Texture()
{
    glGenTextures(1, &mTextureId);
}

Texture::~Texture() {
    glDeleteTextures(1, &mTextureId);
}

void Texture::LoadFile(const GLchar *filePath)
{
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
        printf("Image could not be opened\n");
        return;
    }

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return;
    }

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
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

// "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, mTextureId);

// Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::Bind(Target target)
{
    glBindTexture((GLenum)target, mTextureId);
}

void Texture::Active(SamplerIndex index)
{
    glActiveTexture((GLenum)index);
}

NS_GLH_END