#pragma once

#include"../Hero/Components/IComponent.hpp"
#include"../Hero/Components/Transform.hpp"

struct MoverData : public Hero::IComponent
{
    Hero::TransformData* transform = nullptr;

    Hero::Float3 StartPosition;
    Hero::Float3 TargetPosition;

    float Time;
    float CurrentTime;
    float Speed;
    void GetTarget();

    float alpha;
    float dir = 1.0f;
};

class Mover : public Hero::IComponentSystem<MoverData>
{
public:
    Mover(uint32_t chunkSize) : Hero::IComponentSystem<MoverData>(chunkSize){}

private:
    void dataInit(MoverData* data) override;
    void dataUpdate(MoverData* data) override;
    void dataDestroy(MoverData* data) override;
};