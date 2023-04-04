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
	class Material;
	class Texture;
	class ShaderProgram;
	class Mesh;
	class CubeMap;

	class RESOURCEMANAGER_API ResourceManager
	{
	public:
		ResourceManager(const ResourceManager&) = delete;

		void Init(const std::string& rootAseetsPath);
		void Reload();
		void Save();

		void SetStaticResource();

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
			{
				return (T*)m_resourceMap[filepath];
			}
			else
			{
				for (auto resource : m_resourceMap)
				{
					if (resource.second->GetName() == filepath)
						return (T *)resource.second;
				}
				return nullptr;
			}
		}

		template<class T>
		inline T* CreateResource(const std::string& filepath)
		{
			if (!std::is_base_of<IResource, T>::value)
				return nullptr;

			if (T* resource = GetResource<T>(filepath))
				return resource;

			T* newResource = new T();
			((IResource*)newResource)->SetFileInfo(filepath);

			GetInstance().m_resourceMap.emplace(filepath, newResource);

			if (typeid(T) == typeid(Material))
			{
				m_materialNameList.push_back(((Material*)newResource)->GetName());
			}

			if (typeid(T) == typeid(Mesh))
			{
				m_meshNameList.push_back(((Mesh*)newResource)->GetName());
			}

			if (typeid(T) == typeid(Texture))
			{
				m_textureNameList.push_back(((Texture*)newResource)->GetName());
			}

			if (typeid(T) == typeid(ShaderProgram))
			{
				m_shaderPorgramNameList.push_back(((ShaderProgram*)newResource)->GetName());
			}

			if (typeid(T) == typeid(CubeMap))
			{
				m_cubeMapNameList.push_back(((CubeMap*)newResource)->GetName());
			}

			return newResource;

		}

		void DeleteResource(const std::string& filepath) // penser a delete
		{
			IResource* resource = GetInstance().m_resourceMap[filepath];
			if (resource)
				resource->Unload();
		}

		template<class T>
		std::vector<std::string> GetResourceNameList();

		template<>
		inline std::vector<std::string> GetResourceNameList<Texture>()
		{
			return m_textureNameList;
		}

		template<>
		inline std::vector<std::string> GetResourceNameList<ShaderProgram>()
		{
			return m_shaderPorgramNameList;
		}

		template<>
		inline std::vector<std::string> GetResourceNameList<CubeMap>()
		{
			return m_cubeMapNameList;
		}


		// Static resource

		ShaderProgram* skyboxShader;
		Mesh* cube;

	private:

		ResourceManager() {}

		std::unordered_map<std::string, IResource*> m_resourceMap;
		std::vector<std::string> m_textureNameList, m_materialNameList, m_meshNameList, m_shaderPorgramNameList, m_cubeMapNameList;

		
	};
	
	

}