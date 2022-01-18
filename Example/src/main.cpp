#include<iostream>

#include"Core.hpp"

int main()
{
  Hero::Core core;
  core.addSystem();

  core.start();
  return 0;
}