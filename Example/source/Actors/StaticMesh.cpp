#include "StaticMesh.hpp"
#include "Renderer.hpp"

#include<fstream>
#include<iostream>

StaticMesh::StaticMesh(const Hero::Sid& NewId)
  : Actor(NewId)
{

}

void StaticMesh::Start()
{

}

void StaticMesh::Update()
{

}

void StaticMesh::End()
{
  delete[] transforms;
}

void StaticMesh::SetRenderer(class Renderer* renderer)
{
  rendererRefs = renderer;
  renderer->Register(material, mesh, transforms, count);
}

void StaticMesh::SetMesh(Hero::Mesh* Mesh)
{
  mesh = Mesh;
}

void StaticMesh::SetMaterial(Hero::Material* Material)
{
  material = Material;
}

void StaticMesh::Load(const char* path)
{
  std::ifstream file(path, std::ios::out);

  file>>count;
  transforms = new TransformComponent[count];

  for(int i = 0; i < count; i++)
  {
    float x,y,z;
    file>>x>>y>>z;
    float rx, ry, rz;
    file>>rx>>ry>>rz;
    TransformPositionSet(transforms[i], Hero::Float3(x,y,z));
    TransformRotationSet(transforms[i], Hero::Quaternion(rx, ry, rz));
    TransformUpdate(transforms[i]);
  }

  file.close();
}