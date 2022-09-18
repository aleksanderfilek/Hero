#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Shader.hpp"
#include "../Hero/Graphics/Mesh.hpp"
#include "../Hero/Graphics/Texture.hpp"
#include"../Components/Transform.hpp"

class StaticMesh : public Hero::Actor
{
private:
  Hero::Mesh* mesh;
  Hero::Shader* shader;
  Hero::Texture* texture[2];

  TransformComponent *transforms;
  uint32_t count = 0;

public:
  StaticMesh(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

  void SetMesh(Hero::Mesh* Shader);
  void SetShader(Hero::Shader* Shader);
  void SetTexture(Hero::Texture* Texture, int id);

  void Load(const char* path);
};