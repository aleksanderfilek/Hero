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
  renderer = (ForwardRenderer*)GetOwner()->GetScene()->GetActor(SID("Renderer"));
  renderer->Register(material, mesh, GetOwner()->GetTransformRef());
}

HERO void StaticMesh::SetMesh(Mesh* Mesh)
{
  mesh = Mesh;
}

HERO void StaticMesh::SetMaterial(Material* Material)
{
  material = Material;
}

}