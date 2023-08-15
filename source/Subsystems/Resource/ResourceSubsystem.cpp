#include "ResourceSubsystem.h"
#include "../../Resources/ResourceHandle.h"
#include "../../Utility/Path.h"
#include "../../Core.h"
// #include "Texture.h"
// #include "Shader.h"
// #include "Mesh.h"
// #include "Font.h"

#include <iostream>
#include <fstream>

void ResourceSubsystem::Startup()
{
    // RegisterEngineResources();
}

void ResourceSubsystem::Shutdown()
{
    Clear();
}

ResourceHandle* ResourceSubsystem::Add(StringId Id, const String& Path, bool IsAbsolutePath)
{
    String absolutePath = Path;
    if(!IsAbsolutePath)
    {
        absolutePath = Path::Combine(Core::Get().GetStartupDirectory(), Path);
    }

    std::ifstream file(*absolutePath, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Could not load resource, path: " << Path << std::endl;
        return nullptr;
    }

    int resourceId = 0;
    file.read((char*)&resourceId, sizeof(int));
    uint32_t size = 0;
    file.read((char*)&size, sizeof(uint32_t));

    uint8_t* data = new uint8_t[size];
    file.read((char*)data, size * sizeof(uint8_t));
    file.close();

    ResourceHandle* resource = loaders[resourceId]->Load(data);
    resource->id = resourceId;
    delete[] data;

    resources.Add(Id, resource);

    return resource;
}

void ResourceSubsystem::Remove(StringId Id)
{
    if(!resources.Contains(Id))
    {
        return;
    }
    ResourceHandle* resource = resources[Id];
    loaders[resource->id]->Unload(resource);
    resources.Remove(Id);
}

void ResourceSubsystem::Clear()
{
    for (auto resource : resources)
    {
        loaders[resource.second->id]->Unload(resource.second);
    }
    resources.Clear();
}

class ResourceHandle* ResourceSubsystem::Get(StringId Id)
{
    return resources[Id];
}

bool ResourceSubsystem::Contains(StringId Id) const
{
    return resources.Contains(Id);
}

// void ResourceSubsystem::RegisterEngineResources()
// {
//     // RegisterResource<Texture>();
//     // RegisterResource<Shader>();
//     // RegisterResource<Mesh>();
//     // RegisterResource<Font>();
// }