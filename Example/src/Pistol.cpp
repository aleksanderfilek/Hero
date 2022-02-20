#include"Pistol.hpp"
#include"Components/Transform.hpp"
#include"Graphics/Shader.hpp"
#include"Player.hpp"

Pistol::Pistol()
{

}

void Pistol::begin()
{
    //cube = new Hero::Mesh("bin/assets/cube.he");
}

void Pistol::update()
{
    // Hero::TransformData* data = (Hero::TransformData*)getComponent<Hero::Transform>();
    // ((Player*)data->actor)->shader->setMatrix4f("model", data->modelMatrix);
    // cube->draw();
}

void Pistol::close()
{
    //delete cube;
}