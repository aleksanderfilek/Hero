#pragma once 

#include"IComponent.hpp"
#include"Math.hpp"

namespace Hero
{

struct Transfrom : public IComponent
{
    Float3 position;
    Float3 rotation; // euler angles
    Float3 scale;

    Matrix4x4 modelMatrix;

    bool isDirty = true;
};

class TransformSystem : public IComponentSystem<Transfrom>
{
public:
    HERO TransformSystem(uint32_t _startSize, uint32_t _chunkSize);

    HERO void update() override;

private:
    HERO void dataInit(Transfrom* data) override;
    HERO void dataUpdate(Transfrom* data) override;
    HERO void dataDestroy(Transfrom* data) override;
};

}