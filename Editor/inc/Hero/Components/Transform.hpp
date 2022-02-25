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

    HERO void setPosition(Float3 newPosition);
    HERO void setRotation(Float3 newRotation);
    HERO void setScale(Float3 newScale);
    inline Float3 getLocalPosition()const { return position; }
    HERO Float3 getGlobalPosition() const;
    inline Float3 getRotation()const { return rotation; }
    inline Float3 getLocalScale()const { return scale; }
    HERO Float3 getGlobalScale() const;
    inline TransformData* getParent() const { return parent; }
    HERO void setParent(TransformData* newParent);
    HERO void addChild(TransformData* child, int index = -1);
    HERO void removeChild(int index);
    inline int getChildrenCount() const { return children.size(); }
    inline std::vector<TransformData*> getChildren() const { return children; }
    HERO Float3 forward();
    HERO Float3 up();
    HERO Float3 right();
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