#pragma once 

#include"Transform.hpp"
#include"Math.hpp"
#include"Actor.hpp"

namespace Hero
{

class Camera : public Actor
{
private:
    Float3 eye = Float3::zero();
    Float3 direction = Float3::forward();
    Float3 up = Float3::up();

    Matrix4x4 view;
    Matrix4x4 projection;
public:
    HERO Camera();
    HERO ~Camera();

    inline Matrix4x4 getViewMatrix(){ return view; }
    inline Matrix4x4 getProjectionMatrix(){ return projection; }

    HERO void setPosition(Float3 _position);
    HERO void setRotation(Float3 _rotation);
};

} // namespace Hero
