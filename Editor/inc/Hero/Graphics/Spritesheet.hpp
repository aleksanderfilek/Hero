#pragma once

#include<unordered_map>
#include<string>

#include"Math.hpp"
#include"Texture.hpp"

namespace Hero
{

class Spritesheet
{
private:
  Texture* texture;
  std::unordered_map<std::string, Int4> sprites;

public:
  HERO Spritesheet(const std::string& path);
  HERO ~Spritesheet();

  inline uint32_t getGlId() const { return texture->getGlId(); }
  inline Int4 getRect(const std::string& name) { return sprites[name]; }
  inline const Texture* getTexture() const { return texture; }
};

}