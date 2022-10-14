#include"ForwardRenderer.hpp"

namespace Hero
{

HERO ForwardRenderer::ForwardRenderer(const Sid& NewId)
: Actor(NewId) 
{
  
}

HERO void ForwardRenderer::Start()
{

}

HERO void ForwardRenderer::Update()
{
  currentMaterial = nullptr;

  for(auto materialGroup: groups)
  {
    bool changeShader = (currentMaterial) ? currentMaterial->GetShader() != materialGroup.material->GetShader() : true;
    currentMaterial = materialGroup.material;
    currentMaterial->Bind(changeShader);
    Shader* currentShader = currentMaterial->GetShader();

    for(auto meshGroup: materialGroup.groups)
    {
      for(auto transformSet: meshGroup.transforms)
      {
        int i = 0;
        for(TransformComponent transform: *transformSet)
        {
          currentShader->setMatrix4f(SID("model"), transform.modelMatrix);
          meshGroup.mesh->draw();
        }
      }
    }
  }
}

HERO void ForwardRenderer::End()
{

}

HERO void ForwardRenderer::Register(Material* material,  Mesh* mesh, std::vector<TransformComponent>* transforms)
{
  for(int i = 0; i < groups.size(); i++)
  {
    MaterialGroup& group = groups[i];
    if(group.material == material)
    {
      for(int j = 0; j < group.groups.size() - j; j++)
      {
        MeshGroup& meshGroup = group.groups[j];
        if(meshGroup.mesh == mesh)
        {
          meshGroup.transforms.push_back(transforms);
          return;
        }
      }

      MeshGroup meshGroup;
      meshGroup.mesh = mesh;
      meshGroup.transforms.push_back(transforms);
      group.groups.push_back(meshGroup);
      return;
    }
    else if(group.material->GetShader() == material->GetShader() && (i + 1) < groups.size() && 
      groups[i+1].material->GetShader() != material->GetShader())
    {
      MaterialGroup materialGroup;
      materialGroup.material = material;
      MeshGroup meshGroup;
      meshGroup.mesh = mesh;
      meshGroup.transforms.push_back(transforms);
      materialGroup.groups.push_back(meshGroup);
      groups.insert(groups.begin() + i + 1, materialGroup);
      return;
    }
  }

  MaterialGroup materialGroup;
  materialGroup.material = material;
  MeshGroup meshGroup;
  meshGroup.mesh = mesh;
  meshGroup.transforms.push_back(transforms);
  materialGroup.groups.push_back(meshGroup);
  groups.push_back(materialGroup);
}

}