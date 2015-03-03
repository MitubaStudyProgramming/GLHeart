#include "Buffer.h"

NS_GLH_BEGIN

static Buffer* g_BindedBuffer = NULL;

Buffer *Buffer::GetBinded() {
    return g_BindedBuffer;
}

Buffer::Buffer()
    :mId(0)
{
    glGenBuffers(1, &mId);
}

Buffer::~Buffer() {
    if (g_BindedBuffer == this) g_BindedBuffer = NULL;
    glDeleteBuffers(1, &mId);
}

void Buffer::Bind(Buffer::BufferTarget target) {
    if (g_BindedBuffer == this)
        return;
    g_BindedBuffer = this;
    glBindBuffer((GLenum)target, mId);
}

void Buffer::Data(Buffer::BufferTarget target, GLsizeiptr size, GLvoid const* data, BufferDataUsage usage) {
    Bind(target);
    glBufferData((GLenum)target, size, data, (GLenum)usage);
}

NS_GLH_END