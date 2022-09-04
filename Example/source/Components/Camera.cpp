#include"Camera.hpp"
#include"../Hero/ThirdParty/GL/Gl.hpp"

void CameraInit(CameraComponent& Camera)
{
  glewInit();
  glGenBuffers(1, &Camera.uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER, Camera.uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(Hero::Matrix4x4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, Camera.uboMatrices, 0, 3 * sizeof(Hero::Matrix4x4));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void CameraProjectionSet(CameraComponent& Camera)
{
  Camera.projection = Hero::projectionMatrix(Camera.width, Camera.height, Camera.fov, Camera.near, Camera.far);
  glBindBuffer(GL_UNIFORM_BUFFER, Camera.uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Hero::Matrix4x4), sizeof(Hero::Matrix4x4), &Camera.projection.col[0].x);

  Camera.pixel = Hero::pixelScreenMatrix(Camera.width, Camera.height, 0.0f, 1.0f);
  glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(Hero::Matrix4x4), sizeof(Hero::Matrix4x4), &Camera.pixel.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void CameraViewSet(CameraComponent& Camera, TransformComponent& transform)
{
  Hero::Float3 target = transform.position + TransgormForward(transform);
  Camera.view = Hero::lookAtMatrix(transform.position, target, Hero::Float3::up());
  glBindBuffer(GL_UNIFORM_BUFFER, Camera.uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Hero::Matrix4x4), &Camera.view.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}