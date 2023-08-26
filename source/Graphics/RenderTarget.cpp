#include "RenderTarget.h"
#include"../ThirdParty/GL/Gl.h"

RenderTarget::RenderTarget(Int2 Size, bool EnableDepthBuffer)
{
    size = Size;
    depthBufferEnabled = EnableDepthBuffer;

    glGenFramebuffers(1, &renderBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, renderBufferId);

    glGenTextures(1, &bufferId);
    glBindTexture(GL_TEXTURE_2D, bufferId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, size.X, size.Y);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bufferId, 0);

    if(depthBufferEnabled)
    {
        glGenTextures(1, &depthBufferId);
        glBindTexture(GL_RENDERBUFFER, depthBufferId);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, size.X, size.Y);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthBufferId, 0);
    }

    GLenum bufferType = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &bufferId);

    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    // {
    //     std::cout << "RenderTarget error\n";
    // }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
    if (depthBufferEnabled)
    {
        glDeleteRenderbuffers(1, &depthBufferId);
    }

    glDeleteTextures(1, &bufferId);
    glDeleteFramebuffers(1, &renderBufferId);
}

void RenderTarget::BindBuffers()
{
    glBindFramebuffer(GL_FRAMEBUFFER, renderBufferId);
    glViewport(0, 0, size.X, size.Y);
}

void RenderTarget::UnbindBuffers()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, size.X, size.Y);
}

void RenderTarget::BindTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bufferId);
}

void RenderTarget::BlitToBuffer(uint32_t WriteBufferId, Int2 WrtiteBufferSize)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, renderBufferId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, WriteBufferId);

    glBlitFramebuffer(0, 0, size.X, size.Y, 0, 0, WrtiteBufferSize.X, WrtiteBufferSize.Y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}