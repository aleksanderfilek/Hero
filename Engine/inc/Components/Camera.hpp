#pragma once 

#include"Transform.hpp"
#include"Math.hpp"
#include"IComponent.hpp"

namespace Hero
{

struct CameraData : public IComponent
{
    TransformData* transform = nullptr;

    Matrix4x4 view = Matrix4x4::identity();
    Matrix4x4 projection = Matrix4x4::identity();

    int width = 0;
    int height = 0;
    float fov = 0.0f;
    float near = 0.0f;
    float far = 0.0f;

    HERO void setFOV(float _fov);
    HERO void setPerspective(int _width, int _height, float _FOV, float _near, float _far);
};

class HERO Camera : public IComponentSystem<CameraData>
{
public:
    Camera(uint32_t chunkSize) : IComponentSystem(chunkSize){}

private:
    void dataInit(CameraData* data) override;
    void dataUpdate(CameraData* data) override;
    void dataDestroy(CameraData* data) override;
};

} // namespace Hero
