#include"ForwardRenderer.hpp"
#include "../../Graphics/RenderTarget.hpp"
#include "../../Core/Core.hpp"
#include "../../Systems/Window.hpp"
#include "../../Systems/Resources.hpp"

namespace Hero
{

HERO ForwardRenderer::ForwardRenderer(const Sid& Name)
: Actor(Name) 
{
  System::Window* window = Core::getSystem<System::Window>(SID("Window"));
  Int2 windowSize = window->getSize();
  RenderTargetConfig config;
  config.DepthBuffer = true;
  renderTarget = new RenderTarget(windowSize.x, windowSize.y, 2, &config);

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
      for(int i = 0; i < meshGroup.transforms.size(); i++)
      {
        if(*meshGroup.visibility[i] == false)
        {
          continue;
        }
        currentShader->setMatrix4f(SID("model"), meshGroup.transforms[i]->GetModelMatrix());
        uint32_t id = meshGroup.ids[i];
        uint8_t r = (id & 0x000000FF) >>  0;
        uint8_t g = (id & 0x0000FF00) >>  8;
        uint8_t b = (id & 0x00FF0000) >>  16;
        uint8_t a = (id & 0xFF000000) >>  24;
        currentShader->setFloat4(SID("id"), Float4((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f));
        meshGroup.mesh->draw();
      }
    }
  }
  renderTarget->UnbindBuffers();

  shader->bind();
  shader->setInt(SID("id"), currentVisibleBudder);
  renderTarget->BindTexture();
  quad->draw();
}

HERO void ForwardRenderer::End()
{
  Actor::End();

  delete renderTarget;
  delete quad;
}

HERO void ForwardRenderer::Register(Material* material,  Mesh* mesh, Transform* transform, uint32_t id, bool* visibility)
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
          meshGroup.ids.push_back(id);
          meshGroup.visibility.push_back(visibility);
          return;
        }
      }

      MeshGroup meshGroup;
      meshGroup.mesh = mesh;
      meshGroup.transforms.push_back(transform);
      meshGroup.ids.push_back(id);
      meshGroup.visibility.push_back(visibility);
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
      meshGroup.ids.push_back(id);
      meshGroup.visibility.push_back(visibility);
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
  meshGroup.ids.push_back(id);
  meshGroup.visibility.push_back(visibility);
  materialGroup.groups.push_back(meshGroup);
  groups.push_back(materialGroup);
}

HERO void ForwardRenderer::SetCurrentVisibleBuffer(int Id)
{
  currentVisibleBudder = Id;
}

HERO int ForwardRenderer::GetIdOnPosition(Int2 Position)
{
  glFlush();
  glFinish(); 

  renderTarget->BindBuffers();
  glReadBuffer(GL_COLOR_ATTACHMENT1);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  uint8_t data[4];
  glReadPixels(Position.x, Position.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  int pickedID = data[0] + data[1] * 256 + data[2] * 256*256 + data[3] * 256*256*256;
  renderTarget->UnbindBuffers();

  return pickedID;
}

}