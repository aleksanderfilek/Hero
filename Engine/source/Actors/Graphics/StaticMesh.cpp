#include"StaticMesh.hpp"
#include "../../Systems/ActorScene/ActorScene.hpp"

namespace Hero
{

HERO StaticMesh::StaticMesh(const Sid& NewId)
  : Actor(NewId)
{

}

HERO void StaticMesh::Start()
{
  renderer = (ForwardRenderer*)SceneRef->GetActor(SID("Renderer"));
  if(!renderer)
    return;

  renderer->Register(material, mesh, &transforms);
}

HERO void StaticMesh::Update()
{

}

HERO void StaticMesh::End()
{
  transforms.clear();
}

HERO void StaticMesh::SetMesh(Mesh* Mesh)
{
  mesh = Mesh;
}

HERO void StaticMesh::SetMaterial(Material* Material)
{
  material = Material;
}

HERO void StaticMesh::AddInstance(TransformComponent& transform)
{
  transforms.push_back(transform);
}

}