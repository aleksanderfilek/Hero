#include"Terrain.hpp"
#include"Mesh.hpp"
#include"ThirdParty.hpp"

#include<vector>
#include<cstring>

namespace Hero
{

HERO Terrain::Terrain(const std::string& path, float yScale, float yShift)
{
  int width, height;
  unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

  if(!image)
  {
      std::cout<<"[Terrain] Could not load texture: "<<path<<std::endl;
      exit(-1);
  }

  std::vector<float> positionsVec;

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      unsigned char* texel = image + (j + width * i) * 3;
      unsigned char y = texel[0];

      positionsVec.push_back(-height/2.0f + i);
      positionsVec.push_back( (int)y * yScale - yShift);
      positionsVec.push_back( -width/2.0f + j );
    }
  }

  SOIL_free_image_data(image);

  MeshBuffer<float> positions;
  positions.type = BufferType::vec3;
  positions.length = positionsVec.size();
  positions.array = new float[positions.length * sizeof(float)];
  std::memcpy(positions.array, positionsVec.data(), positions.length * sizeof(float));
  positionsVec.clear();

  std::vector<MeshBuffer<float>> buffers;
  buffers.push_back(positions);

  std::vector<int> indicesVec;
  for(unsigned int i = 0; i < height-1; i++)
  {
    for(unsigned int j = 0; j < width-1; j++)
    {
      indicesVec.push_back(width*i + j);
      indicesVec.push_back(width*i + j+1);
      indicesVec.push_back(width*(i+1) + j+1);

      indicesVec.push_back(width*i + j);
      indicesVec.push_back(width*(i+1) + j+1);
      indicesVec.push_back(width*(i+1) + j);
    }
  }

  MeshBuffer<int> indices;
  indices.length = indicesVec.size();
  indices.array = new int[indices.length * sizeof(int)];
  std::memcpy(indices.array, indicesVec.data(), indices.length * sizeof(int));
  indicesVec.clear();

  mesh = new Mesh("terrain", buffers, indices);
}

HERO Terrain::~Terrain()
{
  delete mesh;
}

HERO void Terrain::draw()
{
  mesh->draw();
}

}