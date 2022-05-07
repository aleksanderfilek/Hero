#pragma once

#include<unordered_map>
#include<string>

#include"../Core/Math.hpp"
#include"../Core/IResource.hpp"

namespace Hero
{

class Spritesheet : public IResource
{
private:
  class Texture* texture;
  std::unordered_map<std::string, Int4> sprites;

public:
  HERO Spritesheet();
  HERO ~Spritesheet();

  HERO static IResource* Load(const std::string& path);
  HERO static void Unload(IResource* resource);
  static int GetId(){ return 4; }

  inline Int4 getRect(const std::string& name) { return sprites[name]; }
  inline const class Texture* getTexture() const { return texture; }
};

}