#include "StaticMesh.hpp"

#include "../Graphics/Mesh.hpp"
#include "../Graphics/Material.hpp"
#include "../Actors/Systems/ForwardRenderer.hpp"
#include "../Systems/ActorScene/Scene.hpp"

namespace Hero
{

HERO StaticMesh::StaticMesh()
{

}

HERO void StaticMesh::Start()
{
  ForwardRenderer* renderer = (ForwardRenderer*)GetOwner()->GetScene()->GetActor(SID("Renderer"));
  renderer->Add(material, mesh, GetOwner()->GetTransformRef(), GetOwner()->GetId(), &visible);
}

HERO void StaticMesh::End()
{
  ForwardRenderer* renderer = (ForwardRenderer*)GetOwner()->GetScene()->GetActor(SID("Renderer"));
  if(!renderer) return;
  renderer->Remove(material, mesh, GetOwner()->GetTransformRef());
}

HERO void StaticMesh::SetMesh(Mesh* Mesh)
{
  mesh = Mesh;
}

HERO void StaticMesh::SetMaterial(Material* Material)
{
  material = Material;
}

HERO void StaticMesh::SetVisibility(bool Visible)
{
  visible = Visible;
}

bool StaticMesh::IsVisible() const
{
  return visible;
}

}