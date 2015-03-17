#include "Framebuffer.h"
#include "Texture.h"

NS_GLH_BEGIN

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &mFBO);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &mFBO);
}

void Framebuffer::Bind(Framebuffer::FramebufferTarget target) {
    glBindFramebuffer((GLenum)target, mFBO);
}

void Framebuffer::Texture2D(FramebufferTarget target, FramebufferAttachment attachment,Texture *texture, GLint level) {
    glFramebufferTexture2D((GLenum)target, (GLenum)attachment, GL_TEXTURE_2D, texture->mTextureId, level);
}

NS_GLH_END