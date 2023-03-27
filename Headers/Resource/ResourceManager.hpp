#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include <iostream>

#include "IResource.hpp"


#ifdef RESOURCEMANAGER_EXPORTS
#define RESOURCEMANAGER_API __declspec(dllexport)
#else
#define RESOURCEMANAGER_API __declspec(dllimport)
#endif

namespace Resource 
{
	class RESOURCEMANAGER_API ResourceManager
	{
	public:
		ResourceManager(const ResourceManager&) = delete;

		void Init(const std::string& rootAseetsPath);

		static ResourceManager& GetInstance()
		{
			static ResourceManager instance;
			return instance;
		}

		
		template<class T>
		inline T* GetResource(const std::string& filepath)
		{
			if (!std::is_base_of<IResource, T>::value)
				return nullptr;

			if (m_resourceMap.count(filepath))
				return (T*)m_resourceMap[filepath];
			else
				return nullptr;
		}

		template<class T>
		inline T* CreateResource(const std::string& filepath)
		{
			if (!std::is_base_of<IResource, T>::value)
				return nullptr;

			if (T* resource = GetResource<T>(filepath))
				return resource;

			T* newResource = new T();


			GetInstance().m_resourceMap.emplace(filepath, newResource);
			return newResource;

		}

		void DeleteResource(const std::string& filepath) // penser a delete
		{
			IResource* resource = GetInstance().m_resourceMap[filepath];
			if (resource)
				resource->Unload();
		}

	private:

		ResourceManager() {}

		std::unordered_map<std::string, IResource*> m_resourceMap;
	};
}