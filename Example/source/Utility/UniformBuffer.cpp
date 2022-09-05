#include"UniformBuffer.hpp"

UniformBuffer::UniformBuffer(uint32_t NewId)
{
  Id = NewId; 
}

void UniformBuffer::Apply()
{
  glewInit();
  glGenBuffers(1, &Ubo);
  glBindBuffer(GL_UNIFORM_BUFFER, Ubo);
  glBufferData(GL_UNIFORM_BUFFER, Size, NULL, GL_STATIC_DRAW);
  
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, Id, Ubo, 0, Size);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}