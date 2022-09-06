#include "Terrain.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Hero/Systems/Resources.hpp"

Terrain::Terrain(const Hero::Sid& NewId) : Hero::Actor(NewId)
{
  Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));
  
  std::string shaderPath("bin/assets/standardShader.he");
  std::string terrainPath("bin/assets/terrain.he");

  resources->Add(SID("standardShader"), shaderPath);
  resources->Add(SID("terrain"), terrainPath);

  Shader = (Hero::Shader*)resources->Get(SID("standardShader"));
  Mesh = (Hero::Mesh*)resources->Get(SID("terrain"));
}

void Terrain::Start()
{

}

void Terrain::Update()
{
  TransformUpdate(Transform);

  Shader->bind();
  Shader->setMatrix4f(SID("model"), Transform.modelMatrix);
  Mesh->draw();
}

void Terrain::End()
{

}