#include"RenderTarget.hpp"

#include"../ThirdParty/GL/Gl.hpp"

namespace Hero
{

HERO RenderTarget::RenderTarget(uint32_t Width, uint32_t Height, ColorChannel Channel, 
    bool DepthBuffer, bool StencilBuffer)
 : Texture(Width, Height, Channel), depthBuffer(DepthBuffer), 
  stencilBuffer(StencilBuffer), clearFlags(GL_COLOR_BUFFER_BIT)
{
  clearFlags |= (DepthBuffer)?GL_DEPTH_BUFFER_BIT:0;
  clearFlags |= (StencilBuffer)?GL_STENCIL_BUFFER_BIT:0;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, glId, 0);

  if(DepthBuffer || StencilBuffer)
  {
    uint32_t storageFlag = 0;
    uint32_t attachmentFlag = 0;
    if(DepthBuffer && StencilBuffer)
    {
      storageFlag = GL_DEPTH24_STENCIL8;
      attachmentFlag = GL_DEPTH_STENCIL_ATTACHMENT;
    }
    else if(DepthBuffer)
    {
      storageFlag = GL_DEPTH_COMPONENT24;
      attachmentFlag = GL_DEPTH_ATTACHMENT;
    }
    else 
    {
      storageFlag = GL_STENCIL_INDEX8;
      attachmentFlag = GL_STENCIL_ATTACHMENT;
    }

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, storageFlag, Width, Height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentFlag, GL_RENDERBUFFER, rbo);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

HERO RenderTarget::~RenderTarget()
{
  glDeleteFramebuffers(1, &fbo);
}

HERO void RenderTarget::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

HERO void RenderTarget::Unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

HERO void RenderTarget::Clear()
{
  if(depthBuffer)
  {
    glEnable(GL_DEPTH_TEST);
  }

  if(stencilBuffer)
  {
    glEnable(GL_STENCIL_TEST);
  }
  
  glClearColor((float)clearColor.r/255.0f, 
    (float)clearColor.g/255.0f, 
    (float)clearColor.b/255.0f, 
    (float)clearColor.a/255.0f);

  glClear(clearFlags);
}

HERO void RenderTarget::SetClearColor(ColorRGB ClearColor)
{
  clearColor = ClearColor;
}

}