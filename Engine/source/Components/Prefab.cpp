#include"Prefab.hpp"
#include"ComponentContext.hpp"
#include"Actor.hpp"
#include"../Utility/ByteOperations.hpp"
#include<fstream>
#include<cstring>
#include"Transform.hpp"

namespace Hero
{

HERO Prefab::Prefab()
{
}

HERO Prefab::Prefab(Sid Name, class Actor* RefActor) : name(Name)
{
  std::vector<IComponent*> components = RefActor->GetAllComponentsData();
  std::vector<Sid> sids = RefActor->GetAllComponentsSid();
  ComponentContext* Context = RefActor->GetComponentContext();

  uint32_t byteSize = 0;
  std::vector<uint32_t> byteSizes;
  for(int Index = 0; Index < sids.size(); Index++)
  {
    byteSize += 2 * sizeof(uint32_t);
    byteSizes.push_back(Context->Get(sids[Index])->GetComponentSize());
    byteSize += byteSizes[byteSizes.size()-1];
  }

  byteSize += 2 * sizeof(uint32_t);
  data = new uint8_t[byteSize];
  size = byteSize;

  //sid, byte size, bytes
  int currentPtr = 0;
  WriteUint32(data, &currentPtr, components.size());
  for(int Index = 0; Index < sids.size(); Index++)
  {
    WriteUint32(data, &currentPtr, sids[Index].id);
    int oldPtr = currentPtr;
    WriteUint32(data, &currentPtr, byteSizes[Index]);
    WritePtr(data, &currentPtr, (void*)RefActor->GetComponent(sids[Index]), byteSizes[Index]);
    componentsData.insert(
      {sids[Index], std::pair<uint8_t*, uint32_t>(data + oldPtr, byteSizes[Index])});
  }
}

HERO Prefab::~Prefab()
{
  if(data)
    delete[] data;

  componentsData.clear();
}

HERO IResource* Prefab::Load(const std::string& path)
{
  Prefab* prefab = new Prefab();

  std::ifstream input(path, std::ios::binary);

  int Id;
  input.read((char*)&Id, sizeof(int));

  if(Id != GetId())
  {
    return nullptr;
  }

  input.read((char*)&prefab->size, sizeof(uint32_t));

  prefab->data = new uint8_t[prefab->size];
  input.read((char*)prefab->data, prefab->size * sizeof(uint8_t));
  input.close();

  int currentPtr = 0;
  prefab->count = ReadUint32(prefab->data, &currentPtr);
  for(int i = 0; i < prefab->count; i++)
  {
    int sidid = ReadUint32(prefab->data, &currentPtr);
    int byteSize = ReadUint32(prefab->data, &currentPtr);
    prefab->componentsData.insert( 
      { Sid(sidid), std::pair<uint8_t*, uint32_t>(prefab->data + currentPtr, byteSize) });
  }

  return prefab;
}

HERO void Prefab::Unload(IResource* resource)
{
  Prefab* prefab = (Prefab*)resource;

  if(prefab->data)
    delete[] prefab->data;

    prefab->componentsData.clear();
}

HERO Actor* Prefab::Spawn(class ComponentContext* Context, Float3 Position, Float3 Rotation, Float3 Scale)
{
  Actor* actor = new Actor(Context);
  uint32_t index = 0;

  actor->AddComponent(SID("Transform"));
  IComponent* Data = actor->GetComponent(SID("Transform"));
  TransformData* Transform = (TransformData*)Data;
  Transform->setPosition(Position);
  Transform->setRotation(Rotation);
  Transform->setScale(Scale);

  for(auto Component: componentsData)
  {
    if(Component.first == SID("Transform"))
      continue;

    actor->AddComponent(Component.first);
    Data = actor->GetComponent(Component.first);
    index = Data->index;
    std::memcpy(Data, Component.second.first, Component.second.second);
    Data->actor = actor;
    Data->index = index;
  }

  return actor;
}

HERO void Prefab::Save(const std::string& path)
{
  std::ofstream output(path, std::ios::binary);

  int Id = GetId();
  output.write((char*)&Id, sizeof(int));
  output.write((char*)&size, sizeof(uint32_t));
  output.write((char*)data, size * sizeof(uint8_t));

  output.close();
}

}