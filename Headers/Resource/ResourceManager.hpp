#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <queue>

#include "Threading/AtomicMutex.hpp"
#include "IResource.hpp"


#include "dllInclude.hpp"

namespace Engine
{
	class Scene;
}

namespace Resource
{
	class Material;
	class Texture;
	class ShaderProgram;
	class Mesh;
	class CubeMap;
	class Prefab;
	class PostProcessingShader;
	class Animation;
	class Audio;

	class PHOSENGINE_API ResourceManager
	{
	public:
		ResourceManager(const ResourceManager&) = delete;

		void Init(const char* rootAseetsPath);
		void LoadAll();
		void Save();
		void Unload();

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
						return (T*)resource.second;
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


			return newResource;

		}

		void DeleteResource(const std::string& filepath) // penser a delete
		{
			IResource* resource = GetInstance().m_resourceMap[filepath];
			if (resource)
				resource->Unload();
		}

		void RenameResource(const std::string& filepath, const std::string& newName);

		

		void SetCurrentScene(Engine::Scene* currentScene);

		std::queue<IResource*> GetQueueToBeBinded() const { return m_toBeBinded; }
		std::unordered_map<std::string, IResource*> GetResourceMap() const { return m_resourceMap; }

		// Static resource

		ShaderProgram* skyboxShader = nullptr;
		ShaderProgram* pickingShader = nullptr;
		ShaderProgram* colorShader = nullptr;
		ShaderProgram* iconShaderForPicking = nullptr;
		ShaderProgram* iconShader = nullptr;
		ShaderProgram* outlineShader = nullptr;
		ShaderProgram* UIShader = nullptr;
		Mesh* cube = nullptr;
		Mesh* sphere = nullptr;
		Mesh* capsule = nullptr;
		Mesh* quad = nullptr;

		Threading::AtomicMutex m_queueMutex;

	private:

		std::queue<IResource*> m_toBeBinded;

		ResourceManager() {}
		void AddResourceByExtension(const std::filesystem::directory_entry& entry,
			const std::string& rootAssetPath);


		std::unordered_map<std::string, IResource*> m_resourceMap;

		Engine::Scene* m_currentScene = nullptr;

	};



}