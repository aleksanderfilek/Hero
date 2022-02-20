#pragma once

#include"Core/Actor.hpp"
#include"Graphics/Mesh.hpp"

class Pistol : public Hero::Actor
{
private:
    Hero::Mesh* cube;

public:
    Pistol();

    void begin() override;
    void update() override;
    void close() override;
};