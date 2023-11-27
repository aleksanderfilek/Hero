#include "ResourceSubsystem.h"
#include "../../Resources/ResourceHandle.h"
#include "../../Utility/PathUtil.h"
#include "../../Core.h"
#include "Loaders/TextureLoader.h"
#include "Loaders/ShaderLoader.h"
#include "Loaders/FontLoader.h"
#include "Loaders/MaterialLoader.h"
#include "Loaders/MeshLoader.h"
#include "Converters/TextureConverter.h"
#include "Converters/ShaderConverter.h"
#include "Converters/FontConverter.h"
#include "Converters/MeshConverter.h"
#include "Converters/MaterialConverter.h"
#include <iostream>
#include <fstream>
#include <string>

ResourceSubsystem* ResourceSubsystem::instance = nullptr;

ResourceSubsystem::ResourceSubsystem()
{
    instance = this;
}

void ResourceSubsystem::Startup()
{
    Subsystem::Startup();

    RegisterEngineResourceLoaders();
}

void ResourceSubsystem::Shutdown()
{
    Subsystem::Shutdown();

    Clear();
}

ResourceHandle* ResourceSubsystem::Add(StringId Id, const char* Path, bool IsAbsolutePath)
{
    const char* absolutePath = Path;
    if(!IsAbsolutePath)
    {
        absolutePath = PathUtil::Combine(Core::Get().GetStartupDirectory(), Path);
    }

    std::ifstream file(absolutePath, std::ios::binary);
    if (!file.is_open())
    {   
        std::cout << "Could not load resource, path: " << absolutePath << std::endl;
        return nullptr;
    }

    uint32_t resourceId = 0;
    file.read((char*)&resourceId, sizeof(uint32_t));
    uint32_t size = 0;
    file.read((char*)&size, sizeof(uint32_t));

    uint8_t* data = new uint8_t[size];
    file.read((char*)data, size * sizeof(uint8_t));
    file.close();

    ResourceHandle* resource = loaders[resourceId]->Load(data, this);
    if(!resource)
    {
        delete[] data;
        return nullptr;
    }

    resource->id = resourceId;
    resource->resourceSubsystem = this;
    delete[] data;

    resources.Add(Id, resource);

    return resource;
}

void ResourceSubsystem::Add(const StringId& Id, ResourceHandle* Resource, const StringId& ResourceId)
{
    Resource->id = ResourceId;
    Resource->resourceSubsystem = this;
    resources.Add(Id, Resource);
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
    for (auto& resource : resources)
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

void ResourceSubsystem::RegisterEngineResourceLoaders()
{
    RegisterResourceLoader<TextureLoader>();
    RegisterResourceLoader<ShaderLoader>();
    RegisterResourceLoader<FontLoader>();
    RegisterResourceLoader<MaterialLoader>();
    RegisterResourceLoader<MeshLoader>();
}

bool ResourceSubsystem::Convert(const char* Path, bool IsAbsolutePath)
{
    std::string path = Path;
    std::string extension = path.substr(path.find_last_of(".") + 1);

    IResourceConverter* converter = nullptr;
    for(auto& converterPair: converters)
    {
        bool found = false;

        Array<const char*> extensions;
        converterPair.second->GetAcceptableExtensions(extensions);
        for(const char* ext: extensions)
        {
            if(ext == extension)
            {
                found = true;
                break;
            }
        }

        if(found)
        {
            converter = converterPair.second;
            break;
        }
    }

    if(!converter)
    {
        return false;
    }

    const char* absolutePath = Path;
    if(!IsAbsolutePath)
    {
        absolutePath = PathUtil::Combine(Core::Get().GetStartupDirectory(), Path);
    }

    converter->Convert(absolutePath);
    return true;
}

void ResourceSubsystem::RegisterEngineResourceConverters()
{
    RegisterResrouceConverter<TextureConverter>();
    RegisterResrouceConverter<ShaderConverter>();
    RegisterResrouceConverter<FontConverter>();
    RegisterResrouceConverter<MeshConverter>();
    RegisterResrouceConverter<MaterialConverter>();
}