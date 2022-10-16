#pragma once 

#include"../../Core/ISystem.hpp"
#include"../../Core/Sid.hpp"

namespace Hero
{

class Scene;

class SceneSystem : public ISystem
{
private:
    Scene* CurrentScene = nullptr;
    Scene* NextScene = nullptr;

public:
    HERO SceneSystem(const Sid& sid, Scene* StartScene);
    HERO ~SceneSystem();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO void ChangeScene(Scene* NewScene);

    inline Scene* GetCurrentScene() { return CurrentScene; }
};

}