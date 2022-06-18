#include"Terrain.hpp"
#include"Mesh.hpp"
#include"../Utility/ByteOperations.hpp"

#include<vector>
#include<cstring>

namespace Hero
{

HERO Terrain::Terrain()
{
}

HERO Terrain::~Terrain()
{
}

HERO ResourceHandle* Terrain::Load(uint8_t* Data, Resources* system)
{
  int index = 0;

  int width = ReadUint32(Data, &index);
  int height = ReadUint32(Data, &index);
  uint32_t imageSize = ReadUint32(Data, &index);
  uint8_t* image = new uint8_t[imageSize];
  ReadPtr(Data, &index, image, imageSize);

  float yScale = 0.0f, yShift = 0.0f;
  ReadPtr(Data, &index, &yScale, sizeof(float));
  ReadPtr(Data, &index, &yShift, sizeof(float));

  int k = 0;
  float* positionArray = new float[height * width * 3];
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      unsigned char* texel = image + (j + width * i) * 3;
      unsigned char y = texel[0];

      positionArray[k++] = -height/2.0f + i;
      positionArray[k++] = (int)y * yScale - yShift;
      positionArray[k++] = -width/2.0f + j;
    }
  }

  delete[] image;

  MeshBuffer<float> positions;
  positions.type = BufferType::vec3;
  positions.length = height * width * 3;
  positions.array = positionArray;

  std::vector<MeshBuffer<float>> buffers;
  buffers.push_back(positions);

  int* indicesArray = new int[height*width*6];
  k=0;
  for(unsigned int i = 0; i < height-1; i++)
  {
    for(unsigned int j = 0; j < width-1; j++)
    {
      indicesArray[k++] = width*i + j;
      indicesArray[k++] = width*i + j+1;
      indicesArray[k++] = width*(i+1) + j+1;
      indicesArray[k++] = width*i + j;
      indicesArray[k++] = width*(i+1) + j+1;
      indicesArray[k++] = width*(i+1) + j;
    }
  }

  MeshBuffer<int> indices;
  indices.length = height*width*6;
  indices.array = indicesArray;

  Terrain* terrain = new Terrain();

  terrain->buffers = buffers;
  terrain->indices = indices;
  terrain->generate();

  return terrain;
}

HERO void Terrain::Unload(ResourceHandle* resource)
{
  delete resource;
}
}