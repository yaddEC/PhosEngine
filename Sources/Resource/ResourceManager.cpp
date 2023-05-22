#include "..\..\..\PhosEditor\External\PhosEngine\Resource\ResourceManager.hpp"
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

void Resource::ResourceManager::Init(const std::string& rootAssetPath)
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
			//std::cout << pool.GetTasks().size() << std::endl;
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
			if (resource.second->isLoaded && !resource.second->isBinded)
			{
				resource.second->Bind();
				resource.second->isBinded = true;
				//std::cout << resource.second->GetName() << " " << count << std::endl;
				count++;
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

	lastRefreshTime = std::chrono::system_clock::now().time_since_epoch();
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

void Resource::ResourceManager::SetStaticResource()
{
	cube = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveCube.obj");
	skyboxShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\SkyboxShader\\SkyboxShader.prog");
	pickingShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\PickingShader\\PickingShader.prog");
	iconShaderForPicking = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\IconShaderForPicking\\IconShaderForPicking.prog");
	iconShader = (ShaderProgram*)m_resourceMap.at("DefaultAssets\\Shader\\BillboardShader\\BillboardShader.prog");
	outlineShader = (ShaderProgram*)m_resourceMap.at("Assets\\Shader\\OutlineShader.prog");
	quad = (Mesh*)m_resourceMap.at("DefaultAssets\\Model\\primitiveQuad.obj");
	shadowShader = (ShaderProgram*)m_resourceMap.at("Assets\\Shader\\ShadowShader.prog");
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
}




