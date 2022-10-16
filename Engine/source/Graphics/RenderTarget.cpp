#include"RenderTarget.hpp"

#include"../ThirdParty/GL/Gl.hpp"

namespace Hero
{

HERO RenderTarget::RenderTarget(uint32_t Width, uint32_t Height, uint32_t Number, RenderTargetConfig* Config)
{
  Size = { (int)Width, (int)Height };
  Count = Number;
  BufferIds = new uint32_t[Number];
  GLenum* DrawBuffers = new GLenum[Count];

  glGenFramebuffers(1, &RenderBufferId);
  glBindFramebuffer(GL_FRAMEBUFFER, RenderBufferId);

  for(int i = 0; i < Count; i++)
  {
    glGenTextures(1, &(BufferIds[i]));
    glBindTexture(GL_TEXTURE_2D, BufferIds[i]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Size.x, Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, BufferIds[i], 0);
    DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
  }

  glGenRenderbuffers(1, &DepthBufferId);
  glBindRenderbuffer(GL_RENDERBUFFER, DepthBufferId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,  Size.x, Size.y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBufferId);
  
  glDrawBuffers(Count, DrawBuffers);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    std::cout<<"RenderTarget error\n";
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

HERO RenderTarget::~RenderTarget()
{
  if(DepthBufferId > 0)
  {
    glDeleteRenderbuffers(1, &DepthBufferId);
  }

  glDeleteTextures(Count, BufferIds);
  glDeleteFramebuffers(1, &RenderBufferId);
  delete[] BufferIds;
}

HERO void RenderTarget::BindBuffers()
{
  glBindFramebuffer(GL_FRAMEBUFFER, RenderBufferId);
  glViewport(0, 0, Size.x, Size.y);
}

HERO void RenderTarget::UnbindBuffers()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, Size.x, Size.y);
}

HERO void RenderTarget::BindTexture()
{
  for(int i = 0; i < Count; i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, BufferIds[i]);
  }
}

HERO void RenderTarget::BlitToBuffer(uint32_t WriteBufferId, Int2 WrtiteBufferSize)
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, RenderBufferId);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, WriteBufferId);

  glBlitFramebuffer(0, 0, Size.x, Size.y, 0, 0, WrtiteBufferSize.x, WrtiteBufferSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}