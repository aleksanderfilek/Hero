#include "Cliff.hpp"
#include "../Hero/Core/Core.hpp"
#include "../Hero/Systems/Resources.hpp"
#include "../Hero/Components/StaticMesh.hpp"
#include "../Hero/Graphics/Mesh.hpp"
#include "../Hero/Graphics/Material.hpp"

Cliff::Cliff(const Hero::Sid& NewId) : Actor(NewId)
{

}

void Cliff::Start()
{
    Hero::Actor::Start();

    Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));

    resources->Add(SID("cliffmesh"), "bin/assets/cliff.he");
    resources->Add(SID("cliffTexture"), "bin/assets/cliffAlbedo.he");
    resources->Add(SID("cliffTextureNormal"), "bin/assets/cliffNormal.he");
    resources->Add(SID("cliffTextureDisplacement"), "bin/assets/cliffDisplacement.he");
    resources->Add(SID("cliffTextureRoughness"), "bin/assets/cliffRoughness.he");
    resources->Add(SID("M_Cliff"), "bin/assets/M_Cliff.he");

    Hero::StaticMesh* staticMesh = new Hero::StaticMesh();
    staticMesh->SetMesh((Hero::Mesh*)resources->Get(SID("cliffmesh")));
    staticMesh->SetMaterial((Hero::Material*)resources->Get(SID("M_Cliff")));
    AddComponent(staticMesh);
}

Hero::Actor* Cliff::Clone()
{
    Hero::Actor* actor = new Cliff(GetName());
    actor->SetTransform(actor->GetTransform());
    return actor;
}