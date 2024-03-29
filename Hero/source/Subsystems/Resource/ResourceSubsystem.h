#pragma once

#include "../Subsystem.h"
#include "../../GenericTypes/StringId.h"
#include "../../Containers/Map.h"
#include "Loaders/IResourceLoader.h"
#include "Converters/IResourceConverter.h"

class HERO_API ResourceSubsystem : public Subsystem
{
private:
	static ResourceSubsystem* instance;

	Map<StringId, class ResourceHandle*> resources;
	Map<StringId, IResourceLoader*> loaders;

public:
	ResourceSubsystem();

	static ResourceSubsystem& Get() { return *instance; }

	virtual void Startup() override;
	virtual void Shutdown() override;

	template<class LoaderClass> void RegisterResourceLoader()
	{
		LoaderClass* loader = new LoaderClass();
		StringId key = loader->GetName();
		loaders.Add(key, loader);
	}

	class ResourceHandle* Add(StringId Id, const char* Path, bool IsAbsolutePath = false);
	void Add(const StringId& Id, class ResourceHandle* Resource, const StringId& ResourceId);
	void Remove(StringId Id);
	void Clear();
	class ResourceHandle* Get(StringId Id);
	bool Contains(StringId Id) const;

public:
	void RegisterEngineResourceLoaders();


private:
	Map<StringId, IResourceConverter*> converters;

public:
	template<class ConverterClass> void RegisterResrouceConverter()
	{
		ConverterClass* converter = new ConverterClass();
		StringId key = converter->GetName();
		converters.Add(key, converter);
	}

	bool Convert(const char* Path, bool IsAbsolutePath = false);
	void RegisterEngineResourceConverters();
};