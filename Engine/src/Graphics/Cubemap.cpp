#include"Cubemap.hpp"
#include"Debug.hpp"
#include"ThirdParty.hpp"

#include<iostream>

namespace Hero
{

HERO Cubemap::Cubemap(const std::vector<std::string> path)
{
  glGenTextures(1, &glId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, glId);

  int width, height, nrChannels;
  for (unsigned int i = 0; i < path.size(); i++)
  {
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(path[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if(!image)
    {
        std::cout<<"Could not load texture: "<< path[i]<<std::endl;
        exit(-1);
    }

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);
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

  mesh = new Mesh("cubemap", buffers, indicies);
}

HERO Cubemap::~Cubemap()
{
  glDeleteTextures(1, &glId);
  glCheckError();

  delete mesh;
}

HERO void Cubemap::draw()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, glId);

  glDepthFunc(GL_LEQUAL);
  mesh->draw();
  glDepthFunc(GL_LESS);
}

}
