#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"

class Cliff : public Hero::Actor
{
private:

public:
    Cliff(const Hero::Sid& NewId);

    void Start() override;

    Hero::Actor* Clone() override;

};