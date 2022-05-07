#include"Mover.hpp"

#include"../Hero/Core/Random.hpp"
#include"../Hero/Components/Actor.hpp"
#include"../Hero/Core/Time.hpp"

#include<iostream>

void MoverData::GetTarget()
{
    StartPosition = transform->position;

    TargetPosition.x = Hero::randomGetFloat(0.0f, 1280.0f);
    TargetPosition.y = Hero::randomGetFloat(0.0f, 720.0f);
    TargetPosition.z = 0.0f;

    Time = Hero::randomGetFloat(0.0f, 5.0f);
    CurrentTime = Time;
}

void Mover::dataInit(MoverData* data)
{
    data->Speed = Hero::randomGetFloat(1.0f, 5.0f);
    data->transform = (Hero::TransformData*)data->actor->GetComponent(SID("Transform"));
    //data->GetTarget();

    float y = Hero::randomGetFloat(0.0f, 720.0f);

    data->StartPosition = Hero::Float3(0.0f, y, 0.0f);
    data->TargetPosition = Hero::Float3(1280.0f, y, 0.0f);

    data->alpha = Hero::randomGetFloat(0.0f, 1.0f);
}

void Mover::dataUpdate(MoverData* data)
{
    // float Alpha = data->CurrentTime/data->Time;

    // data->transform->position = Hero::lerp(data->TargetPosition, data->StartPosition, Alpha);

    // data->CurrentTime -= data->Speed * Hero::Time::getDeltaTime();

    // if(data->CurrentTime <= 0.0f)
    // {
    //     data->GetTarget();
    // }

    data->transform->position = Hero::lerp(data->StartPosition, data->TargetPosition, data->alpha);

    data->alpha += data->dir * Hero::Time::getDeltaTime();

    if(data->alpha > 1.0f || data->alpha < 0.0f)
        data->dir = -1.0f * data->dir;
}

void Mover::dataDestroy(MoverData* data)
{

}