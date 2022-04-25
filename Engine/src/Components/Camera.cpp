#include"Camera.hpp"
#include"Actor.hpp"
#include"ThirdParty.hpp"

namespace Hero
{

HERO void CameraData::setFOV(float _fov)
{
  Type = CameraPerspective::Projection;
  fov = _fov;
  projection = projectionMatrix(width, height, _fov, near, far);
  glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4x4), sizeof(Matrix4x4), &projection.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

HERO void CameraData::setProjection(int _width, int _height, float _fov, float _near, float _far)
{
  Type = CameraPerspective::Projection;
  width = _width;
  height = _height;
  fov = _fov;
  near = _near;
  far = _far;
  projection = projectionMatrix(width, height, fov, near, far);
  glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4x4), sizeof(Matrix4x4), &projection.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  pixel = pixelScreenMatrix(width, height, 0.0f, 1.0f);
  glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(Matrix4x4), sizeof(Matrix4x4), &pixel.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

HERO void CameraData::setOrthogonal(int _width, int _height, float _near, float _far)
{
  Type = CameraPerspective::Orthogonal;
  width = _width;
  height = _height;
  near = _near;
  far = _far;
  projection = orthographicMatrix(width, height, near, far);
  glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4x4), sizeof(Matrix4x4), &projection.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

HERO void Camera::dataInit(CameraData* data)
{
  data->transform = (TransformData*)data->actor->GetComponent(SID("Transform"));

  data->view = lookAtMatrix(data->transform->position, data->transform->forward(), Float3::up());

  glGenBuffers(1, &data->uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER, data->uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(Matrix4x4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, data->uboMatrices, 0, 3 * sizeof(Matrix4x4));

  glBindBuffer(GL_UNIFORM_BUFFER, data->uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix4x4), &data->view.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

HERO void Camera::dataUpdate(CameraData* data)
{
  Float3 target = data->transform->position + data->transform->forward();
  data->view = lookAtMatrix(data->transform->position, target, Float3::up());
  glBindBuffer(GL_UNIFORM_BUFFER, data->uboMatrices);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix4x4), &data->view.col[0].x);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

HERO void Camera::dataDestroy(CameraData* data)
{

}

}