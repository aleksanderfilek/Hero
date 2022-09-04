#include"Cubemap.hpp"
#include"../Core/Debug.hpp"
#include"../ThirdParty/GL/Gl.hpp"
#include"Mesh.hpp"
#include"../Utility/ByteOperations.hpp"
#include"../Utility/Qoi.hpp"

#include<iostream>

namespace Hero
{

HERO Cubemap::Cubemap()
{}

HERO ResourceHandle* Cubemap::Load(uint8_t* Data, Resources* system)
{
  int index = 0;

  uint32_t glId;
  glGenTextures(1, &glId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, glId);

  uint32_t width = ReadUint32(Data, &index);
  uint32_t height = ReadUint32(Data, &index);
  uint8_t channel = ReadUint8(Data, &index);
  uint32_t glChannel = (channel == 3)? GL_RGB : GL_RGBA;

  for(int i = 0; i < 6; i++)
  {
    uint32_t byteSize = ReadUint32(Data, &index);

    uint8_t* imageData = new uint8_t[byteSize];
    ReadPtr(Data, &index, imageData, byteSize);
    uint8_t* image = QOI::Decode(imageData, byteSize, width, height, channel);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
      0, glChannel, width, height, 0, glChannel, GL_UNSIGNED_BYTE, image);

    delete[] imageData;
    delete[] image;
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  MeshBuffer<float> position;
  position.type = BufferType::vec3;
  position.array = new float[24]{ 
    -1.0f, -1.0f, -1.0f, 
     1.0f, -1.0f, -1.0f,
     1.0f, 1.0f, -1.0f,
     -1.0f, 1.0f, -1.0f,
     -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     -1.0f, 1.0f, 1.0f
  };
  position.length = 24;

  std::vector<MeshBuffer<float>> buffers;
  buffers.push_back(position);

  MeshBuffer<int> indicies;
  indicies.array = new int[36]{
    1, 5, 6,
    1, 6, 2,

    0, 7, 4,
    0, 3, 7,

    3, 2, 6,
    3, 6, 7,

    0, 5, 1,
    0, 4, 5,

    4, 6, 5,
    4, 7, 6,
    
    0, 1, 2,
    0, 2, 3
  };
  indicies.length = 36;

  Cubemap* cubemap = new Cubemap();

  cubemap->buffers = buffers;
  cubemap->indices = indicies;
  cubemap->glId = glId;
  cubemap->generate();

  return cubemap;
}

HERO void Cubemap::Unload(ResourceHandle* resource)
{
  delete resource;
}

HERO Cubemap::~Cubemap()
{
  glDeleteTextures(1, &glId);
  glCheckError();
}

HERO void Cubemap::draw()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, glId);

  glDepthFunc(GL_LEQUAL);
  Mesh::draw();
  glDepthFunc(GL_LESS);
}

}
