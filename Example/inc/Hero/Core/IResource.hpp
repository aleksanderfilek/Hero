#pragma once

#include<string>

namespace Hero
{

class IResource
{
public:
  int id;
};

struct ResourceFunctions
{
  IResource* (*Load)(const std::string& path);
  void (*Unload)(IResource* Resource);
};

}