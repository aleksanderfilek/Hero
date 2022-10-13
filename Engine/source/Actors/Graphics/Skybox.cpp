#include"Skybox.hpp"

#include"../../Core/Core.hpp"
#include"../../Systems/Resources.hpp"
#include "../../Graphics/Material.hpp"
#include "../../Graphics/Cubemap.hpp"
#include "../Systems/ForwardRenderer.hpp"
#include "../../Systems/ActorScene/ActorScene.hpp"

#include<iostream>

namespace Hero
{

HERO Skybox::Skybox(const Sid& NewId)
 : Actor(NewId)
{

}

HERO void Skybox::Start()
{
  ForwardRenderer* renderer = (ForwardRenderer*)SceneRef->GetActor(SID("Renderer"));
  if(!renderer)
    return;

  TransformComponent startTransform;
  transform.push_back(startTransform);
  renderer->Register(material, cubemap, &transform);
}

HERO void Skybox::Update()
{

}

HERO void Skybox::End()
{

}

HERO void Skybox::SetMaterial(class Material* Material)
{
  material = Material;
}

HERO void Skybox::SetCubemap(Cubemap* Cubemap)
{
  cubemap = Cubemap;
}

}