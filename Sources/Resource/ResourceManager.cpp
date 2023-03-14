// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ShaderProgram.hpp"

#define RESOURCE_PATH "Resources"

#define RESOURCEMANAGER_EXPORTS
#include "Resource/ResourceManager.hpp"

using namespace Resource;

namespace fs = std::filesystem;

std::string GetExtension(const fs::directory_entry& entry)
{

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

			if (GetExtension(entry) == "png" || GetExtension(entry) == "PNG" || GetExtension(entry) == "jpg" || GetExtension(entry) == "JPG" || GetExtension(entry) == "rgba")
			{
				CreateResource<Texture>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (GetExtension(entry) == "obj" || GetExtension(entry) == "OBJ")
			{
				//CreateResource<Mesh>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (GetExtension(entry) == "prog" || GetExtension(entry) == "PROG")
			{
				CreateResource<ShaderProgram>(GetRelativePath(entry, rootAseetsPath));
			}
		}
	}

	for (auto resource : m_resourceMap)
	{
		resource.second->Load(resource.first);
	}

	for (auto resource : m_resourceMap)
	{
		resource.second->Bind();
	}
}