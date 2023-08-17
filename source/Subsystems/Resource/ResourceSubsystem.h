#pragma once

#include "../Subsystem.h"
#include "../../GenericTypes/StringId.h"
#include "../../Containers/Map.h"
#include "Loaders/IResourceLoader.h"

class HERO_API ResourceSubsystem : public Subsystem
{
private:
	Map<StringId, class ResourceHandle*> resources;
	Map<StringId, class IResourceLoader*> loaders;

public:
	virtual void Startup() override;
	virtual void Shutdown() override;

	template<class LoaderClass> bool RegisterResourceLoader()
	{
		LoaderClass* loader = new LoaderClass();
		StringId key = loader->GetName();
		loaders.Add(key, loader);
	}

	class ResourceHandle* Add(StringId Id, const String& Path, bool IsAbsolutePath = false);
	void Remove(StringId Id);
	void Clear();
	class ResourceHandle* Get(StringId Id);
	bool Contains(StringId Id) const;

protected:
	void RegisterEngineResourceLoaders();
};