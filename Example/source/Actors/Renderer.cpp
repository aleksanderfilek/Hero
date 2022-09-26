#include"Renderer.hpp"

Renderer::Renderer(const Hero::Sid& NewId)
: Hero::Actor(NewId) 
{
  
}

void Renderer::Start()
{

}

void Renderer::Update()
{
  for(auto materialGroup: groups)
  {
    if(currentShader != materialGroup.material->GetShader())
    {
      currentShader = materialGroup.material->GetShader();
      currentShader->bind();
    }

    materialGroup.material->Bind();

    for(auto meshGroup: materialGroup.groups)
    {
      for(auto transformSet: meshGroup.transforms)
      {
        for(int i = 0; i < transformSet.second; i++)
        {
          currentShader->setMatrix4f(SID("model"), transformSet.first[i].modelMatrix);
          meshGroup.mesh->draw();
        }
      }
    }
  }
}

void Renderer::End()
{

}

void Renderer::Register(Hero::Material* material,  Hero::Mesh* mesh, TransformComponent* transforms, uint32_t count)
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
          meshGroup.transforms.push_back(std::pair<TransformComponent*, uint32_t>(transforms, count));
          return;
        }
      }

      MeshGroup meshGroup;
      meshGroup.mesh = mesh;
      meshGroup.transforms.push_back(std::pair<TransformComponent*, uint32_t>(transforms, count));
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
      meshGroup.transforms.push_back(std::pair<TransformComponent*, uint32_t>(transforms, count));
      materialGroup.groups.push_back(meshGroup);
      groups.insert(groups.begin() + i + 1, materialGroup);
      return;
    }
  }

  MaterialGroup materialGroup;
  materialGroup.material = material;
  MeshGroup meshGroup;
  meshGroup.mesh = mesh;
  meshGroup.transforms.push_back(std::pair<TransformComponent*, uint32_t>(transforms, count));
  materialGroup.groups.push_back(meshGroup);
  groups.push_back(materialGroup);
}