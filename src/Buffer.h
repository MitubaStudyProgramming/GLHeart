#pragma once

#include "Predefine.h"

NS_GLH_BEGIN

class Buffer
{
public:
    enum BufferTarget
    {
        ARRAY_BUFFER = GL_ARRAY_BUFFER,
        COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
        COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
        ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
        PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
        PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
        TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
        TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
        UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
    };

    static Buffer* GetBinded();
public:
    Buffer();
    ~Buffer();

    void Bind(BufferTarget target);

    void Data(BufferTarget target, GLsizeiptr size, GLvoid const* data, BufferDataUsage usage);

private:
    GLuint mId;
};

NS_GLH_END