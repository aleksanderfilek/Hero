#include"Spritesheet.hpp"
#include"Texture.hpp"
#include"Color.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/Qoi.hpp"

#include<fstream>

namespace Hero
{

HERO Spritesheet::Spritesheet()
{}

HERO Spritesheet::~Spritesheet()
{
  sprites.clear();
  delete texture;
}

HERO IResource* Spritesheet::Load(const std::string& path)
{
  std::ifstream file(path, std::ios::binary);

  std::string texturePath;
  char* temp;
  uint32_t size;

  int ResourceId;
  file.read((char*)&ResourceId, sizeof(int));

  uint32_t spritesCount;
  file.read((char*)&spritesCount, sizeof(uint32_t));

  Spritesheet* spritesheet = new Spritesheet();

  for(int i = 0; i < spritesCount; i++)
  {
    file.read((char*)&size, sizeof(uint32_t));
    temp = new char[size+1];
    file.read(temp, size * sizeof(char));
    temp[size] = '\0';
    std::string name = temp;
    delete[] temp;

    Int4 rect;
    file.read((char*)&rect.x, sizeof(uint32_t));
    file.read((char*)&rect.y, sizeof(uint32_t));
    file.read((char*)&rect.z, sizeof(uint32_t));
    file.read((char*)&rect.w, sizeof(uint32_t));

    spritesheet->sprites.insert({name, rect});
  }

  uint32_t width, height;
  file.read((char*)&width, sizeof(uint32_t));
  file.read((char*)&height, sizeof(uint32_t));
  uint8_t channels;
  file.read((char*)&channels, sizeof(uint8_t));
  uint8_t colorSpace;
  file.read((char*)&colorSpace, sizeof(uint8_t));
  uint8_t flags;
  file.read((char*)&flags, sizeof(uint8_t));
  uint32_t ByteLength;
  file.read((char*)&ByteLength, sizeof(uint32_t));

  uint8_t* Data = new  uint8_t[ByteLength];
  file.read((char*)Data, ByteLength*sizeof(char));

  file.close();

  uint8_t* image = QOI::Decode(Data+1, ByteLength, width, height, channels);

  delete[] Data;

  unsigned int gl_id;
  glGenTextures(1, &gl_id);
  glCheckError();
  glBindTexture(GL_TEXTURE_2D, gl_id);
  glCheckError();
  
  int param = (flags & 1)?GL_LINEAR: GL_NEAREST;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
  glCheckError();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glCheckError();

  uint32_t glChannel = (channels == 3)? GL_RGB : GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, glChannel, width, height, 0, 
      glChannel, GL_UNSIGNED_BYTE, image);
  glCheckError();

  if(flags & 2){
      glGenerateMipmap(GL_TEXTURE_2D);
      glCheckError();
  }

  delete[] image;
  glBindTexture(GL_TEXTURE_2D, 0);
  glCheckError();

  Texture* texture = new Texture(path, gl_id, (Int2){ (int)width, (int)height },
    flags, (channels == 3)?ColorChannel::RGB : ColorChannel::RGBA,
    (colorSpace == 0)?ColorSpace::SRGB : ColorSpace::Linear);

  spritesheet->texture = texture;

  return spritesheet;
}

HERO void Spritesheet::Unload(IResource* resource)
{
  Spritesheet* spritesheet = static_cast<Spritesheet*>(resource);
  spritesheet->sprites.clear();
  delete spritesheet->texture;
}

}