#include"Skybox.hpp"

#include"../../Core/Core.hpp"
#include"../../Systems/Resources.hpp"
#include "../../Graphics/Material.hpp"
#include "../Systems/ForwardRenderer.hpp"
#include "../../Systems/ActorScene/Scene.hpp"

#include<iostream>

namespace Hero
{

HERO Skybox::Skybox(const Sid& Name)
 : Actor(Name)
{

}

HERO void Skybox::Start()
{
  Actor::Start();

  ForwardRenderer* renderer = (ForwardRenderer*)GetScene()->GetActor(SID("Renderer"));
  if(!renderer)
    return;

  renderer->Register(material, cubemap, GetTransformRef(), GetId());
}

HERO void Skybox::Update()
{
  Actor::Update();
}

HERO void Skybox::End()
{
  Actor::End();
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