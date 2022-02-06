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
public:
    HERO Camera(int width, int height, float FOV, float near, float far);
    HERO ~Camera();

    void begin() override;
    void update() override;
    void close() override;

    inline Matrix4x4 getViewMatrix(){ return view; }
    inline Matrix4x4 getProjectionMatrix(){ return projection; }
};

} // namespace Hero
