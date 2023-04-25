// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ResourceIncludes.hpp"
#include "Wrapper/GUI.hpp"

#include "Resource/ResourceManager.hpp"

using namespace Resource;

namespace fs = std::filesystem;

std::string GetExtension(const fs::directory_entry& entry)
{
	if (entry.path().u8string().find_last_of('.') == std::string::npos)
		return "";
	return strrchr(entry.path().u8string().c_str(), '.') + 1;
}

std::string GetRelativePath(const fs::directory_entry& entry, const std::string& rootDirectory)
{
	std::string pathStr = entry.path().u8string().substr();
	return pathStr.substr(pathStr.find(rootDirectory));
}

void ResourceManager::Init(const std::string& rootAseetsPath)
{

	for (const auto& entry : fs::recursive_directory_iterator(rootAseetsPath))
	{
		if (!fs::is_directory(entry))
		{
			std::string extension = GetExtension(entry);

			if (extension == "png" || extension == "PNG" || extension == "jpg" || extension == "JPG" || extension == "rgba")
			{
				CreateResource<Texture>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "obj" || extension == "OBJ" || extension == "fbx" || extension == "FBX")
			{
				CreateResource<Mesh>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "prog" || extension == "PROG")
			{
				CreateResource<ShaderProgram>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "phmat" || extension == "PHMAT")
			{
				CreateResource<Material>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "phcm" || extension == "PHCM")
			{
				CreateResource<CubeMap>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "phprefab" || extension == "PHPREFAB")
			{
				CreateResource<Prefab>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (extension == "phscene" || extension == "PHSCENE")
			{
				CreateResource<Engine::Scene>(GetRelativePath(entry, rootAseetsPath));
			}
		}
	}
}

void Resource::ResourceManager::Reload()
{
	for (auto resource : m_resourceMap)
	{
		if (resource.second->GetTypeName() != "Scene")
			resource.second->Load(resource.first);
	}

	for (auto resource : m_resourceMap)
	{
		resource.second->Bind();
	}
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
}

void Resource::ResourceManager::SetCurrentScene(Engine::Scene* currentScene) 
{
	m_currentScene = currentScene;
}




