#include"Cubemap.hpp"
#include"../Core/Debug.hpp"
#include"../ThirdParty/GL/Gl.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include"../ThirdParty/Stb/stb_image.h"
#include"Mesh.hpp"

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
    int width, height, nrChannels;
    unsigned char *image = stbi_load(path[i].c_str(), &width, &height, &nrChannels, 0);

    if(!image)
    {
        std::cout<<"Could not load texture: "<< path[i]<<std::endl;
        exit(-1);
    }

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
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

  mesh = new Mesh(buffers, indicies);
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
