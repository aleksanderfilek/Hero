#pragma once 

#include"IComponent.hpp"
#include"Math.hpp"

#include<vector>

namespace Hero
{

struct HERO TransformData : public IComponent
{
    Float3 position = Float3::zero();
    Float3 rotation = Float3::zero(); // euler angles
    Float3 scale = Float3::one();

    Matrix4x4 modelMatrix;
    bool isDirty = true;

    TransformData* parent = nullptr;
    std::vector<TransformData*> children;

    void setPosition(Float3 newPosition);
    void setRotation(Float3 newRotation);
    void setScale(Float3 newScale);
    inline Float3 getLocalPosition()const { return position; }
    Float3 getGlobalPosition() const;
    inline Float3 getRotation()const { return rotation; }
    inline Float3 getLocalScale()const { return scale; }
    Float3 getGlobalScale() const;
    inline TransformData* getParent() const { return parent; }
    void setParent(TransformData* newParent);
    void addChild(TransformData* child, int index = -1);
    void removeChild(int index);
    inline int getChildrenCount() const { return children.size(); }
    inline std::vector<TransformData*> getChildren() const { return children; }
};

class HERO Transform : public IComponentSystem<TransformData>
{
public:
    Transform(uint32_t _startSize, uint32_t _chunkSize);

    void update() override;

private:
    void dataInit(TransformData* data) override;
    void dataUpdate(TransformData* data) override;
    void dataDestroy(TransformData* data) override;
};

}