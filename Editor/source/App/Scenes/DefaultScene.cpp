#include"DefaultScene.hpp"

#include"../../Hero/Core/Core.hpp"
#include"../../Hero/Systems/Resources.hpp"

void DefaultScene::begin()
{
    Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("Resources"));
    std::string spritebatchPath = "resources/spritebatch.he";
    resources->Add(SID("SpriteBatch_Shader"), spritebatchPath);
    std::string papajPath = "resources/papaj.he";
    resources->Add(SID("Papaj_Image"), papajPath);
}

void DefaultScene::update()
{

}

void DefaultScene::close()
{

}