#pragma once 

#include"Transform.hpp"
#include"Math.hpp"
#include"IComponent.hpp"

namespace Hero
{

enum class CameraPerspective : uint8_t
{
    Projection = 0,
    Orthogonal = 1
};

struct CameraData : public IComponent
{
    TransformData* transform = nullptr;
    uint32_t uboMatrices;

    CameraPerspective Type = CameraPerspective::Projection;

    Matrix4x4 view = Matrix4x4::identity();
    Matrix4x4 projection = Matrix4x4::identity();

    int width = 0;
    int height = 0;
    float fov = 0.0f;
    float near = 0.0f;
    float far = 0.0f;

    HERO void setFOV(float _fov);
    HERO void setPerspective(int _width, int _height, float _fov, float _near, float _far);
    HERO void setOrthogonal(int width, int height, float near, float far);
};

class HERO Camera : public IComponentSystem<CameraData>
{
public:
    Camera(uint32_t chunkSize) : IComponentSystem(chunkSize){}

private:
    HERO void dataInit(CameraData* data) override;
    HERO void dataUpdate(CameraData* data) override;
    HERO void dataDestroy(CameraData* data) override;
};

} // namespace Hero
