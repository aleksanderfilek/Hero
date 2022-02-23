#include"Pistol.hpp"
#include"Components/Transform.hpp"
#include"Graphics/Shader.hpp"
#include"Player.hpp"
#include"Core/Time.hpp"

#include<iostream>

Pistol::Pistol()
{

}

void Pistol::begin()
{
    cube = new Hero::Mesh("bin/assets/cube.he");
}

void Pistol::update()
{
    float deltaTime = Hero::Time::getDeltaTime();
    Hero::TransformData* data = (Hero::TransformData*)getComponent<Hero::Transform>();

    Hero::Float3 rotation = data->getRotation();
    rotation.z += 10.0f * deltaTime;
    data->setRotation(rotation);

    Player* player = (Player*)data->getParent()->actor;
    player->shader->bind();
    player->shader->setMatrix4f("model", data->modelMatrix);
    cube->draw();
}

void Pistol::close()
{
    delete cube;
}