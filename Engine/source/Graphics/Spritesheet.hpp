#pragma once

#include<unordered_map>
#include<string>

#include"../Core/Math.hpp"
#include"../Systems/Resources.hpp"
#include"../Core/Sid.hpp"

namespace Hero
{

class Spritesheet : public ResourceHandle
{
private:
  class Texture* texture;
  std::unordered_map<Sid, Int4, SidHashFunction> sprites;

public:
  HERO Spritesheet();
  HERO ~Spritesheet();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return SPRITESHEET_ID; }

  inline Int4 getRect(const Sid& name) { return sprites[name]; }
  inline const class Texture* getTexture() const { return texture; }
};

}