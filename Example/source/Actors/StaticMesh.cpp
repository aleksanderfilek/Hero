#include "StaticMesh.hpp"

#include<iostream>
#include<fstream>

StaticMesh::StaticMesh(const Hero::Sid& NewId)
  : Actor(NewId)
{

}

void StaticMesh::Start()
{
  std::cout<<mesh->Count()<<std::endl;
}

void StaticMesh::Update()
{
  shader->bind();
  for(int i = 0; i < texture.size(); i++)
  {
    texture[i]->bind(i);
  }

  for(int i = 0; i < count; i++)
  {
    shader->setMatrix4f(SID("model"), transforms[i].modelMatrix);
    mesh->draw();
  }
}

void StaticMesh::End()
{
  delete[] transforms;
}

void StaticMesh::SetMesh(Hero::Mesh* Mesh)
{
  mesh = Mesh;
}

void StaticMesh::SetShader(Hero::Shader* Shader)
{
  shader = Shader;
}

void StaticMesh::SetTexture(Hero::Texture* Texture, int id)
{
  if(texture.size() > id)
  {
    texture[id] = Texture;
    return;
  }
  texture.push_back(Texture);
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