#include"RenderTarget.hpp"

#include"../ThirdParty/GL/Gl.hpp"

namespace Hero
{

HERO RenderTarget::RenderTarget(uint32_t Width, uint32_t Height, uint32_t Number, RenderTargetConfig* Config)
{
  glGenFramebuffers(1, &RenderBufferId);
  glBindFramebuffer(GL_FRAMEBUFFER, RenderBufferId);

  Size = { (int)Width, (int)Height };
  Count = Number;
  BufferIds = new uint32_t[Number];
  
  int format = GL_RGBA;
  for(int i = 0; i < Number; i++)
  {
    format = (Config == nullptr)? GL_RGBA : ( Config->Format.size() < i) ? Config->Format[i] : format;

    glGenTextures(1, &BufferIds[i]);
    glBindTexture(GL_TEXTURE_2D, BufferIds[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, format, Width, Height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, BufferIds[i], 0);
  }

  glDrawBuffers(Count, BufferIds);

  if(Config != nullptr && Config->DepthBuffer)
  {
    glGenRenderbuffers(1, &DepthBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, DepthBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBufferId);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

HERO RenderTarget::~RenderTarget()
{
  glDeleteTextures(Count, BufferIds);
  glDeleteFramebuffers(1, &RenderBufferId);
}

HERO void RenderTarget::BindBuffers()
{
  glBindFramebuffer(GL_FRAMEBUFFER, RenderBufferId);
  glViewport(0, 0, Size.x, Size.y);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawBuffers(Count, BufferIds);
}

HERO void RenderTarget::BindTexture()
{
  for(int i = 0; i < Count; i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, BufferIds[i]);
  }
}

}