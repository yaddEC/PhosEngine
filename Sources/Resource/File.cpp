// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/IResource.hpp"
#include "Resource/File.hpp"

void Resource::File::SetFileData(const std::string& filepath)
{
	m_directory = filepath.substr(0, filepath.find_last_of('\\'));
	m_filename = filepath.substr(m_directory.size() + 1, filepath.find_last_of('.'));
	m_extension = filepath.substr(filepath.find_last_of('.') + 1);
}

void Resource::File::ReloadAllResourcesInFile()
{
	for (auto resource : m_resourceInFile)
	{
		resource->Unload();
		resource->Load();
	}
}

void Resource::File::CreateAllResourceInFile()
{
	std::string filepath = GetFilepath();

	std::string extension = m_extension;
	ResourceManager& rm = Resource::ResourceManager::GetInstance();

	std::vector<IResource*> newResources;

	if (extension == "png" || extension == "PNG" || extension == "jpg" || extension == "JPG" || extension == "rgba")
	{
		newResources.push_back(rm.CreateResource<Texture>(filepath));
	}
	else if (extension == "obj" || extension == "OBJ" || extension == "fbx" || extension == "FBX")
	{
		newResources.push_back(rm.CreateResource<Mesh>(filepath));
	}
	else if (extension == "anim" || extension == "ANIM")
	{
		newResources.push_back(rm.CreateResource<Animation>(filepath));
	}
	else if (extension == "prog" || extension == "PROG")
	{
		newResources.push_back(rm.CreateResource<ShaderProgram>(filepath));
	}
	else if (extension == "phmat" || extension == "PHMAT")
	{
		newResources.push_back(rm.CreateResource<Material>(filepath));
	}
	else if (extension == "phcm" || extension == "PHCM")
	{
		newResources.push_back(rm.CreateResource<CubeMap>(filepath));
	}
	else if (extension == "phprefab" || extension == "PHPREFAB")
	{
		newResources.push_back(rm.CreateResource<Prefab>(filepath));
	}
	else if (extension == "phscene" || extension == "PHSCENE")
	{
		newResources.push_back(rm.CreateResource<Engine::Scene>(filepath));
	}
	else if (extension == "phppro" || extension == "PHPPRO")
	{
		newResources.push_back(rm.CreateResource<PostProcessingShader>(filepath));
	}
	else // text file
	{

	}

	for (auto resource : newResources)
	{
		resource->SetFileInfo(filepath);
		m_resourceInFile.push_back(resource);
	}
}
