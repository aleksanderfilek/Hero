#include"Cubemap.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Hero/Systems/Resources.hpp"
#include"../Hero/Graphics/Mesh.hpp"

#include<iostream>

Cubemap::Cubemap(const Hero::Sid& NewId) : Hero::Actor(NewId)
{
  Hero::Resources* resources = nullptr;
  resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));

  std::string cubemapPath("bin/assets/cubemap.he");
  resources->Add(SID("cubemap"), cubemapPath);
  cubemap = (Hero::Cubemap*)resources->Get(SID("cubemap"));

  std::string shaderPath("bin/assets/cubemapShader.he");
  resources->Add(SID("cubemapShader"), shaderPath);
  shader = (Hero::Shader*)resources->Get(SID("cubemapShader"));
}

void Cubemap::Start()
{

}

void Cubemap::Update()
{
  shader->bind();
  cubemap->draw();
}

void Cubemap::End()
{

}