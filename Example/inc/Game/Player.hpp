#pragma once

#include"IComponent.hpp"
#include"Transform.hpp"
#include"Input.hpp"

struct PlayerData : public Hero::IComponent
{
    Hero::TransformData* transform = nullptr;
    Hero::System::Input* input = nullptr;

    float yaw = 0.0f;
    float pitch = 0.0f;
};

class Player : public Hero::IComponentSystem<PlayerData>
{
public:
    Player(uint32_t chunkSize) : Hero::IComponentSystem<PlayerData>(chunkSize){}


private:
    void dataInit(PlayerData* data) override;
    void dataUpdate(PlayerData* data) override;
    void dataDestroy(PlayerData* data) override;
};