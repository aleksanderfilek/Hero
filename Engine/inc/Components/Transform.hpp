#pragma once 

#include"IComponent.hpp"
#include"Math.hpp"

namespace Hero
{

struct TransformData : public IComponent
{
    Float3 position = Float3::zero();
    Float3 rotation = Float3::zero(); // euler angles
    Float3 scale = Float3::one();

    Matrix4x4 modelMatrix;

    bool isDirty = true;
};

class Transform : public IComponentSystem<TransformData>
{
public:
    HERO Transform(uint32_t _startSize, uint32_t _chunkSize);

    HERO void update() override;

private:
    HERO void dataInit(TransformData* data) override;
    HERO void dataUpdate(TransformData* data) override;
    HERO void dataDestroy(TransformData* data) override;
};

}