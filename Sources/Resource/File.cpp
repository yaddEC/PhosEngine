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

	IResource* newResource = nullptr;

	if (extension == "png" || extension == "PNG" || extension == "jpg" || extension == "JPG" || extension == "rgba")
	{
		newResource = rm.CreateResource<Texture>(filepath);
	}
	else if (extension == "obj" || extension == "OBJ" || extension == "fbx" || extension == "FBX")
	{
		newResource = rm.CreateResource<Mesh>(filepath);
	}
	else if (extension == "anim" || extension == "ANIM")
	{
		newResource = rm.CreateResource<Animation>(filepath);
	}
	else if (extension == "prog" || extension == "PROG")
	{
		newResource = rm.CreateResource<ShaderProgram>(filepath);
	}
	else if (extension == "phmat" || extension == "PHMAT")
	{
		newResource = rm.CreateResource<Material>(filepath);
	}
	else if (extension == "phcm" || extension == "PHCM")
	{
		newResource = rm.CreateResource<CubeMap>(filepath);
	}
	else if (extension == "phprefab" || extension == "PHPREFAB")
	{
		newResource = rm.CreateResource<Prefab>(filepath);
	}
	else if (extension == "phscene" || extension == "PHSCENE")
	{
		newResource = rm.CreateResource<Engine::Scene>(filepath);
	}
	else if (extension == "phppro" || extension == "PHPPRO")
	{
		newResource = rm.CreateResource<PostProcessingShader>(filepath);
	}
	else // text file
	{

	}

	if (newResource)
	{
		newResource->SetFileInfo(filepath);
		m_resourceInFile.push_back(newResource);
	}
}
