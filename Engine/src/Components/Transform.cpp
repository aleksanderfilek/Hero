#include"Transform.hpp"

namespace Hero
{

HERO Float3 TransformData::getGlobalPosition() const
{
    Float3 global = position;
    TransformData* tParent = parent;
    while(tParent)
    {
        global = global + tParent->position;
        tParent = tParent->parent;
    }
    return global;
}

HERO Float3 TransformData::getGlobalScale() const
{
    Float3 global = scale;
    TransformData* tParent = parent;
    while(tParent)
    {
        global = global * tParent->scale;
        tParent = tParent->parent;
    }
    return global;
}

HERO void TransformData::setPosition(Float3 newPosition)
{
    isDirty  = true;
    position = newPosition;
}

HERO void TransformData::setRotation(Float3 newRotation)
{
    isDirty  = true;
    rotation = newRotation;
}

HERO void TransformData::setScale(Float3 newScale)
{
    isDirty  = true;
    scale = newScale;
}

HERO void TransformData::setParent(TransformData* newParent)
{
    isDirty = true;
    parent = newParent;
    parent->children.push_back(this);
}

HERO void TransformData::addChild(TransformData* child, int index)
{
    if(index == -1)
        children.push_back(child);
    else
        children.insert(children.begin() + index, child);

    child->parent = this;
}

HERO void TransformData::removeChild(int index)
{
    children.erase(children.begin() + index);
}

HERO Float3 TransformData::forward()
{
  Matrix4x4 rotationMatrix = Matrix4x4::identity();
  rotateXYZ(rotationMatrix, rotation);
  Float4 tforward = rotationMatrix * Float4(0.0f, 0.0f, 1.0f, 0.0f);
  Float3 forward(tforward);
  forward.normalize();
  return forward;
}

HERO Float3 TransformData::up()
{
  Matrix4x4 rotationMatrix = Matrix4x4::identity();
  rotateXYZ(rotationMatrix, rotation);
  Float4 tup = rotationMatrix * Float4(0.0f, 1.0f, 0.0f, 0.0f);
  Float3 up(tup);
  up.normalize();
  return up;
}

HERO Float3 TransformData::right()
{
  Matrix4x4 rotationMatrix = Matrix4x4::identity();
  rotateXYZ(rotationMatrix, rotation);
  Float4 tright = rotationMatrix * Float4(1.0f, 0.0f, 0.0f, 0.0f);
  Float3 right(tright);
  right.normalize();
  return right;
}


HERO void Transform::update()
{
    // update modelMatrix
    for(auto& component: data)
    {
        if(!component.first)
            continue;

        TransformData& transform = component.second;

        // if(!component.isDirty)
        //     continue;

        transform.modelMatrix = TRS(
            transform.position, transform.rotation, transform.scale);
        transform.isDirty = false;
    }

    // update hierarchy
    for(auto& component: data)
    {
        if(!component.first)
            continue;

        TransformData& transform = component.second;

        //std::cout<<"ptr = "<<(int*)transform.parent<<std::endl;

        if(transform.parent != nullptr)
        {        
            // std::cout<<transform.parent->modelMatrix<<std::endl;
            // std::cout<<transform.modelMatrix<<std::endl;
        
            transform.modelMatrix = transform.parent->modelMatrix * transform.modelMatrix;

            // std::cout<<transform.modelMatrix<<std::endl;
        }
    }
}

HERO void Transform::dataInit(TransformData* data)
{
    data->modelMatrix = TRS(
        data->position, data->rotation, data->scale);
    data->isDirty = false;
}

HERO void Transform::dataUpdate(TransformData* data)
{
    data->modelMatrix = TRS(
        data->position, data->rotation, data->scale);
    data->isDirty = false;
}

HERO void Transform::dataDestroy(TransformData* data)
{
    
}

}