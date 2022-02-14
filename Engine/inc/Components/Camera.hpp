#pragma once 

#include"Transform.hpp"
#include"Math.hpp"
#include"Actor.hpp"

namespace Hero
{

class Camera : public Actor
{
private:
    TransformData* transform;

    Matrix4x4 view;
    Matrix4x4 projection;
    Matrix4x4 invProjection;

    int width;
    int height;
    float fov;
    float near;
    float far;
public:
    HERO Camera(int _width, int _height, float _FOV, float _near, float _far);
    HERO ~Camera();

    void begin() override;
    void update() override;
    void close() override;

    inline Matrix4x4 getViewMatrix(){ return view; }
    inline Matrix4x4 getProjectionMatrix(){ return projection; }

    HERO void setFOV(float _fov);
};

} // namespace Hero
