#include"Transform.hpp"
#include"../Systems/Profiler.hpp"
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
    isDirty  = 1;
    position = newPosition;
}

HERO void TransformData::setRotation(Float3 newRotation)
{
    isDirty  = 1;
    rotation = newRotation;
}

HERO void TransformData::setScale(Float3 newScale)
{
    isDirty  = 1;
    scale = newScale;
}

HERO void TransformData::setParent(TransformData* newParent)
{
    isDirty = 1;
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

HERO Transform::Transform(uint32_t chunkSize, bool _CanUpdate) 
: IComponentSystem(chunkSize), CanUpdate(_CanUpdate)
{}

HERO void Transform::update()
{
    if(!CanUpdate)
        return;

    // update modelMatrix
    for(auto& component: data)
    {
        if(!component.first)
            continue;

        TransformData& transform = component.second;

        if(transform.isDirty == 0)
            continue;

        uint64_t start = System::Profiler::GetTime();
        transform.modelMatrix = TRS(
        transform.position, transform.rotation, transform.scale);
        transform.isDirty = false;
        uint64_t end = System::Profiler::GetTime();
        //System::Profiler::Register(SID("TRS"), end - start);

        transform.isDirty = (transform.parent == nullptr)? 0 : 2;
    
    }

    // update hierarchy
    for(auto& component: data)
    {
        if(!component.first)
            continue;

        TransformData& transform = component.second;

        if(transform.isDirty != 2)
            continue;

        //std::cout<<"ptr = "<<(int*)transform.parent<<std::endl;
     
            // std::cout<<transform.parent->modelMatrix<<std::endl;
            // std::cout<<transform.modelMatrix<<std::endl;
        uint64_t start = System::Profiler::GetTime();
        transform.modelMatrix = transform.parent->modelMatrix * transform.modelMatrix;
        uint64_t end = System::Profiler::GetTime();
        //System::Profiler::Register(SID("mul"), end - start);
            // std::cout<<transform.modelMatrix<<std::endl;

        transform.isDirty = 0;
    }
}

HERO void Transform::dataInit(TransformData* data)
{
    data->modelMatrix = TRS(
        data->position, data->rotation, data->scale);
    data->isDirty = 0;
}

HERO void Transform::dataUpdate(TransformData* data)
{
    data->modelMatrix = TRS(
        data->position, data->rotation, data->scale);
    data->isDirty = 0;
}

HERO void Transform::dataDestroy(TransformData* data)
{
    
}

}