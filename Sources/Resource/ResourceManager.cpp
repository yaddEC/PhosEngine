// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ShaderProgram.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Material.hpp"
#include "Wrapper/GUI.hpp"

#define RESOURCEMANAGER_EXPORTS
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

			if (GetExtension(entry) == "png" || GetExtension(entry) == "PNG" || GetExtension(entry) == "jpg" || GetExtension(entry) == "JPG" || GetExtension(entry) == "rgba")
			{
				CreateResource<Texture>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (GetExtension(entry) == "obj" || GetExtension(entry) == "OBJ" || GetExtension(entry) == "fbx" || GetExtension(entry) == "FBX")
			{
				CreateResource<Mesh>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (GetExtension(entry) == "prog" || GetExtension(entry) == "PROG")
			{
				CreateResource<ShaderProgram>(GetRelativePath(entry, rootAseetsPath));
			}
			else if (GetExtension(entry) == "phmat" || GetExtension(entry) == "PHMAT")
			{
				CreateResource<Material>(GetRelativePath(entry, rootAseetsPath));
			}
		}
	}	
}

void Resource::ResourceManager::Reload() 
{
	for (auto resource : m_resourceMap)
	{
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
		resource.second->Save();
	}
}


//template<class T>
//inline T* ResourceManager::ResourceListGUI(T* selected)
//{
//	std::vector<T*> list;
//	if (typeid(T) == typeid(Material))
//	{
//		list = m_materialList;
//	}
//
//	if (typeid(T) == typeid(Mesh))
//	{
//		list = m_meshList;
//	}
//
//	if (typeid(T) == typeid(Texture))
//	{
//		list = m_textureList;
//	}
//
//	if (typeid(T) == typeid(ShaderProgram))
//	{
//		list = m_shaderProgramList;
//	}
//
//	using namespace Wrapper;
//
//	
//	for (T* resource : list)
//	{
//		Maths::Vec2 cursorPos = Wrapper::GUI::GetCursorPos();
//
//		Wrapper::GUI::SetCursorPos(cursorPos + Maths::Vec2(0, 4));
//
//
//		Wrapper::GUI::BeginGroup();
//		if (m_fileIcons.count(file) && m_fileIcons.at(file))
//		{
//			Resource::Texture* icon = m_fileIcons.at(file);
//			icon->DisplayImage(100);
//		}
//		else
//		{
//			m_defaultFileIcon->DisplayImage(100);
//		}
//
//		std::string displayfilename = resource;
//		displayfilename = displayfilename.substr(displayfilename.find_last_of('\\') + 1);
//
//		if (Wrapper::GUI::TruncTextBySize(displayfilename, 90))
//			displayfilename += "...";
//
//		Wrapper::GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - Wrapper::GUI::CalcTextSize(displayfilename).x) * 0.5f, cursorPos.y + 110));
//
//		Wrapper::GUI::DisplayText(displayfilename);
//		Wrapper::GUI::EndGroup();
//
//		if (Wrapper::GUI::IsItemDoubleClicked(0))
//		{
//			return resource;
//		}
//	}
//
//	resource nullptr;
//}
