#include"Spritesheet.hpp"
#include"Texture.hpp"
#include"Color.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/Qoi.hpp"
#include"../Utility/ByteOperations.hpp"

namespace Hero
{

HERO Spritesheet::Spritesheet()
{}

HERO Spritesheet::~Spritesheet()
{
  sprites.clear();
  delete texture;
}

HERO ResourceHandle* Spritesheet::Load(uint8_t* Data, Resources* system)
{
  int index = 0;
  uint32_t size;
  int id;

  uint32_t spritesCount = ReadUint32(Data, &index);

  Spritesheet* spritesheet = new Spritesheet();

  for(int i = 0; i < spritesCount; i++)
  {
    size = ReadUint32(Data, &index);
    id = ReadUint32(Data, &index);
    Sid name(id);

    Int4 rect;
    rect.x = ReadInt(Data, &index);
    rect.y = ReadInt(Data, &index);
    rect.z = ReadInt(Data, &index);
    rect.w = ReadInt(Data, &index);

    spritesheet->sprites.insert(std::pair<Sid, Int4>(name, rect));
  }

  uint32_t width, height;
  width = ReadUint32(Data, &index);
  height = ReadUint32(Data, &index);
  uint8_t channels = ReadUint8(Data, &index);;
  uint8_t colorSpace = ReadUint8(Data, &index);;
  uint8_t flags = ReadUint8(Data, &index);;
  uint32_t ByteLength = ReadUint32(Data, &index);

  uint8_t* imgData = new  uint8_t[ByteLength];
  ReadPtr(Data, &index, imgData, ByteLength);

  uint8_t* image = QOI::Decode(imgData+1, ByteLength, width, height, channels);

  delete[] imgData;

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

  Texture* texture = new Texture(gl_id, (Int2){ (int)width, (int)height },
    flags, (channels == 3)?ColorChannel::RGB : ColorChannel::RGBA,
    (colorSpace == 0)?ColorSpace::SRGB : ColorSpace::Linear);

  spritesheet->texture = texture;

  return spritesheet;
}

HERO void Spritesheet::Unload(ResourceHandle* resource)
{
  delete resource;
}

}