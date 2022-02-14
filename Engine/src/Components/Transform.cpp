#include"Transform.hpp"

namespace Hero
{

static Matrix4x4 createModelMatrix(Float3 pos, Float3 rot, Float3 sc)
{
    Matrix4x4 model = Matrix4x4::identity();
    rotateXYZM4x4(&model, rot);
    scaleM4x4(&model, sc);
    translateM4x4(&model, pos);
    return model;
}

Float3 TransformData::getGlobalPosition() const
{
    Float3 global = position;
    TransformData* tParent = parent;
    while(tParent)
    {
        global = addF3(global, tParent->position);
        tParent = tParent->parent;
    }
    return global;
}

Float3 TransformData::getGlobalScale() const
{
    Float3 global = scale;
    TransformData* tParent = parent;
    while(tParent)
    {
        global = multiplyF3F3(global, tParent->scale);
        tParent = tParent->parent;
    }
    return global;
}

void TransformData::setPosition(Float3 newPosition)
{
    isDirty  = true;
    position = newPosition;
}

void TransformData::setRotation(Float3 newRotation)
{
    isDirty  = true;
    rotation = newRotation;
}

void TransformData::setScale(Float3 newScale)
{
    isDirty  = true;
    scale = newScale;
}

void TransformData::setParent(TransformData* newParent)
{
    isDirty = true;
    parent = newParent;
    parent->children.push_back(this);
}

void TransformData::addChild(TransformData* child, int index)
{
    if(index == -1)
        children.push_back(child);
    else
        children.insert(children.begin() + index, child);

    child->parent = this;
}

void TransformData::removeChild(int index)
{
    children.erase(children.begin() + index);
}

HERO Transform::Transform(uint32_t _startSize, uint32_t _chunkSize) 
    : IComponentSystem(_startSize, _chunkSize)
{

}

HERO void Transform::update()
{
    for(auto& component: data)
    {
        if(!component.first || !component.second.isDirty) continue;

        TransformData& transform = component.second;

        transform.modelMatrix = createModelMatrix(
            transform.position, transform.rotation, transform.scale);
        transform.isDirty = false;

        TransformData* parent = transform.parent;
        while(parent)
        {
            bool stop = parent->isDirty;

            if(parent->isDirty)
            {
                parent->modelMatrix = createModelMatrix(
                    parent->position, parent->rotation, parent->scale);
                parent->isDirty = false;
            }

            transform.modelMatrix = multiplyM4x4(
                parent->modelMatrix, transform.modelMatrix);
            parent = (stop)?nullptr : parent->parent;
        }
    }   
}

HERO void Transform::dataInit(TransformData* data)
{
    data->modelMatrix = createModelMatrix(
        data->position, data->rotation, data->scale);
    data->isDirty = false;
}

HERO void Transform::dataUpdate(TransformData* data)
{
    data->modelMatrix = createModelMatrix(
        data->position, data->rotation, data->scale);
    data->isDirty = false;
}

HERO void Transform::dataDestroy(TransformData* data)
{
    
}

}