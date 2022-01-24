#include"Spritesheet.hpp"

#include<fstream>

namespace Hero
{

HERO Spritesheet::Spritesheet(const std::string& path)
{

  std::ifstream input(path, std::ios::binary);

  std::string texturePath;
  char* temp;
  uint32_t size;

  input.read((char*)&size, sizeof(uint32_t));
  temp = new char[size+1];
  input.read(temp, size * sizeof(char));
  temp[size] = '\0';
  texturePath = temp;
  delete[] temp;

  uint32_t spritesCount;
  input.read((char*)&spritesCount, sizeof(uint32_t));

  for(int i = 0; i < spritesCount; i++)
  {
    input.read((char*)&size, sizeof(uint32_t));
    temp = new char[size+1];
    input.read(temp, size * sizeof(char));
    temp[size] = '\0';
    std::string name = temp;
    delete[] temp;

    Int4 rect;
    input.read((char*)&rect.x, sizeof(uint32_t));
    input.read((char*)&rect.y, sizeof(uint32_t));
    input.read((char*)&rect.z, sizeof(uint32_t));
    input.read((char*)&rect.w, sizeof(uint32_t));

    sprites.insert({name, rect});
  }

  input.close();

  texture = new Texture(texturePath.c_str(), 
    (uint8_t)TextureFlag::NEAREST | (uint8_t)TextureFlag::NO_MIPMAP);
}

HERO Spritesheet::~Spritesheet()
{
  sprites.clear();
  delete texture;
}

}