#include"ForwardRenderer.hpp"
#include "../../Graphics/RenderTarget.hpp"
#include "../../Core/Core.hpp"
#include "../../Systems/Window.hpp"
#include "../../Systems/Resources.hpp"

namespace Hero
{

HERO ForwardRenderer::ForwardRenderer(const Sid& NewId)
: Actor(NewId) 
{
  System::Window* window = Core::getSystem<System::Window>(SID("Window"));
  Int2 windowSize = window->getSize();
  RenderTargetConfig config;
  config.DepthBuffer = true;
  renderTarget = new RenderTarget(windowSize.x, windowSize.y, 1, &config);

  std::vector<MeshBuffer<float>> buffers;
  MeshBuffer<float> positions;
  positions.array = new float[8]{-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
  positions.type = BufferType::vec2;
  positions.length = 8;

  MeshBuffer<float> uvs;
  uvs.array = new float[8]{0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  uvs.type = BufferType::vec2;
  uvs.length = 8;

  buffers.push_back(positions);
  buffers.push_back(uvs);

  MeshBuffer<int> indices;
  indices.array = new int[6]{0, 2, 1, 2, 3, 1};
  indices.type = BufferType::single;
  indices.length = 6;
  quad = new Mesh(buffers, indices);
}

HERO void ForwardRenderer::Start()
{
  Actor::Start();

  Resources* resources = Core::getSystem<Resources>(SID("resources"));
  shader = (Shader*)resources->Get(SID("rendererShader"));
}

HERO void ForwardRenderer::Update()
{
  Actor::Update();

  renderTarget->BindBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  currentMaterial = nullptr;

  for(auto materialGroup: groups)
  {
    bool changeShader = (currentMaterial) ? currentMaterial->GetShader() != materialGroup.material->GetShader() : true;
    currentMaterial = materialGroup.material;
    currentMaterial->Bind(changeShader);
    Shader* currentShader = currentMaterial->GetShader();

    for(auto meshGroup: materialGroup.groups)
    {
      for(auto transform: meshGroup.transforms)
      {
        currentShader->setMatrix4f(SID("model"), transform->GetModelMatrix());
        meshGroup.mesh->draw();
      }
    }
  }
  renderTarget->UnbindBuffers();

  shader->bind();
  renderTarget->BindTexture();
  quad->draw();
}

HERO void ForwardRenderer::End()
{
  Actor::End();

  delete renderTarget;
  delete quad;
}

HERO void ForwardRenderer::Register(Material* material,  Mesh* mesh, Transform* transform)
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
          meshGroup.transforms.push_back(transform);
          return;
        }
      }

      MeshGroup meshGroup;
      meshGroup.mesh = mesh;
      meshGroup.transforms.push_back(transform);
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
      meshGroup.transforms.push_back(transform);
      materialGroup.groups.push_back(meshGroup);
      groups.insert(groups.begin() + i + 1, materialGroup);
      return;
    }
  }

  MaterialGroup materialGroup;
  materialGroup.material = material;
  MeshGroup meshGroup;
  meshGroup.mesh = mesh;
  meshGroup.transforms.push_back(transform);
  materialGroup.groups.push_back(meshGroup);
  groups.push_back(materialGroup);
}

}