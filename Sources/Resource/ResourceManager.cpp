// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ResourceIncludes.hpp"
#include "Wrapper/GUI.hpp"

#include "Threading/PoolSystem.hpp"
#include "Threading/Thread.hpp"

#include "Resource/ResourceManager.hpp"

using namespace Resource;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::system_clock::duration duration;

namespace fs = std::filesystem;

std::string GetExtension(const fs::directory_entry& entry)
{
	if (entry.path().u8string().find_last_of('.') == std::string::npos)
		return "";
	return strrchr(entry.path().string().c_str(), '.') + 1;
}

std::string GetRelativePath(const fs::directory_entry& entry, const std::string& rootDirectory)
{
	std::string pathStr = entry.path().string().substr();
	return pathStr.substr(pathStr.find(rootDirectory));
}

void Resource::ResourceManager::Init(const char* rootAssetPath)
{
	for (const auto& entry : fs::recursive_directory_iterator(rootAssetPath))
	{
		if (!fs::is_directory(entry))
		{
			AddResourceByExtension(entry, rootAssetPath);
		}
	}
}

void Resource::ResourceManager::LoadAll()
{
	Threading::Pool pool;

	
	for (auto resource : m_resourceMap)
	{
		if (resource.second->GetTypeName() != "Scene" && !resource.second->isLoaded)
		{
			pool.registerTask(Threading::ResourceTask
				{
					[](void* resource)
					{
						((IResource*)resource)->Load();
						((IResource*)resource)->isLoaded = true;
					},
					resource.second
				});
		}
	}

	for (int i = 0; i < 5; i++)
	{
		pool.registerThread(new Threading::Thread(pool, std::to_string(i)));
	}
	pool.startPool();

	int count = 0;

	while (true)
	{
		bool allResourceAreLoaded = true;
		for (auto resource : m_resourceMap)
		{
			if (resource.second->isLoaded && !resource.second->isBinded && resource.second->GetTypeName() != "Scene")
			{
				resource.second->Bind();
				resource.second->isBinded = true;
				count++;
				std::cout << resource.first << " " << count << " / " << m_resourceMap.size() << std::endl;
			}
			if (!resource.second->isLoaded && resource.second->GetTypeName() != "Scene")
				allResourceAreLoaded = false;
		}

		if (allResourceAreLoaded)
		{
			break;
		}
	}
	std::cout << "All resources are loaded" << std::endl;
	pool.stopPool();
	pool.~Pool();

}



void Resource::ResourceManager::Save()
{
	for (auto resource : m_resourceMap)
	{
		if (resource.second->GetTypeName() != "Scene")
			resource.second->Save();
	}
	if(m_currentScene)
		m_currentScene->Save();
}

void Resource::ResourceManager::Unload()
{
	m_currentScene->Unload();
	for (auto resource : m_resourceMap)
	{
		if (resource.second->isLoaded && resource.second->isBinded)
		{
			resource.second->Unload();
		}
		delete resource.second;
	}
	m_resourceMap.clear();
}

void Resource::ResourceManager::SetStaticResource()
{
	cube = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveCube.obj");
	sphere = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveSphere.obj");
	capsule = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveCapsule.obj");
	skyboxShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\SkyboxShader\\SkyboxShader.prog");
	pickingShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\PickingShader\\PickingShader.prog");
	iconShaderForPicking = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\IconShaderForPicking\\IconShaderForPicking.prog");
	iconShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\BillboardShader\\BillboardShader.prog");
	outlineShader = (ShaderProgram*)m_resourceMap.at("Assets\\Shader\\OutlineShader.prog");
	UIShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\UIShader\\UIShader.prog");
	colorShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\ColorShader\\ColorShader.prog");
	quad = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveQuad.obj");
}

void Resource::ResourceManager::RenameResource(const std::string& filepath, const std::string& newName)
{
	if (m_resourceMap.count(filepath))
	{
		IResource* resource = m_resourceMap.at(filepath);
		resource->SetName(newName);
		m_resourceMap.erase(filepath);
		m_resourceMap.emplace(resource->GetFilePath(), resource);
	}
}

void Resource::ResourceManager::SetCurrentScene(Engine::Scene* currentScene)
{
	m_currentScene = currentScene;
}

void Resource::ResourceManager::AddResourceByExtension(const fs::directory_entry& entry, const std::string& rootAssetPath)
{
	std::string extension = GetExtension(entry);

	if (extension == "png" || extension == "PNG" || extension == "jpg" || extension == "JPG" || extension == "rgba")
	{
		CreateResource<Texture>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "obj" || extension == "OBJ" || extension == "fbx" || extension == "FBX")
	{
		CreateResource<Mesh>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "anim" || extension == "ANIM")
	{
		CreateResource<Animation>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "prog" || extension == "PROG")
	{
		CreateResource<ShaderProgram>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phmat" || extension == "PHMAT")
	{
		CreateResource<Material>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phcm" || extension == "PHCM")
	{
		CreateResource<CubeMap>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phprefab" || extension == "PHPREFAB")
	{
		CreateResource<Prefab>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phscene" || extension == "PHSCENE")
	{
		CreateResource<Engine::Scene>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phppro" || extension == "PHPPRO")
	{
		CreateResource<PostProcessingShader>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "phcanvas" || extension == "PHCANVAS")
	{
		CreateResource<UI::Canvas>(GetRelativePath(entry, rootAssetPath));
	}
	else if (extension == "wav" || extension == "WAV" || extension == "mp3" || extension == "MP3")
	{
		CreateResource<Audio>(GetRelativePath(entry, rootAssetPath));
	}
}




