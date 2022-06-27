#pragma once

#include"../../Hero/Systems/Scene.hpp"

class DefaultScene : public Hero::System::IScene
{
public:
  void begin() override;
  void update() override;
  void close() override;
};