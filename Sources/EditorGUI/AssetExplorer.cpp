#include "EditorGUI/AssetExplorer.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/IResource.hpp"
#include "Wrapper/GUI.hpp"

namespace fs = std::filesystem;
using namespace std;
using namespace EditorGUI;

AssetExplorer::AssetExplorer(const std::string& rootDirectory)
	: IEditorGUI("Assets", true), m_assetsRootDirectory(rootDirectory), m_currentDirectory(rootDirectory)
{

}

AssetExplorer::~AssetExplorer()
{
	for (auto icon : m_fileIcons)
	{
		delete icon.second;
	}
}

string GetFileExtension(const string& filename)
{
	return filename.substr(filename.find_last_of('.') + 1);
}

void AssetExplorer::Reload()
{
	cout << "Reloading..." << endl;
	for (const auto& entry : fs::recursive_directory_iterator(m_assetsRootDirectory))
	{
		string entryName = entry.path().u8string();
		Resource::IResource* resource = Resource::ResourceManager::GetInstance().GetResource<Resource::IResource>(entryName);
		if (resource && m_fileIcons.count(entryName) == 0)
		{
			cout << entryName << endl;
			m_fileIcons.emplace(entryName, resource->GenerateFileIcon());
		}
	}
}

void AssetExplorer::DoUpdate()
{
	GUI::DisplayText(m_currentDirectory);
	GUI::Separator();

	if (m_currentDirectory != m_assetsRootDirectory)
	{
		if (GUI::Button("..."))
		{
			m_currentDirectory = m_currentDirectory.substr(0, m_currentDirectory.find_last_of('\\'));
			return;
		}
	}


	for (const auto& entry : fs::directory_iterator(m_currentDirectory))
	{
		string entryName = entry.path().u8string();

		if (fs::is_directory(entry))
		{
			GUI::BeginGroup();
			Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\folderWhite.png")->DisplayImage(90);
			if (GUI::Button(entryName.substr(entryName.find_last_of('\\') + 1).c_str()))
			{
				m_currentDirectory = entryName;
				GUI::EndGroup();
				return;
			}
			GUI::EndGroup();
		}
		else
		{
			DisplayFile(entry.path().u8string());
		}

		GUI::SameLine(35);
	}

}

void AssetExplorer::DisplayFile(const string& file)
{
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	Maths::Vec2 cursorPos = GUI::GetCursorPos();

	GUI::BeginGroup();
	if (m_fileIcons.count(file) && m_fileIcons.at(file))
	{
		Resource::Texture* icon = m_fileIcons.at(file);
		icon->DisplayImage(90);
	}
	else
	{
		Resource::Texture* icon = rm.GetResource<Resource::Texture>("DefaultAssets\\whiteFile.png");
		if (icon)
		{
			icon->DisplayImage(90);
			
		}
	}


	// TEMP
	std::string displayfilename = file;
	displayfilename = displayfilename.substr(displayfilename.find_last_of('\\') + 1);
	//float textWidth = 90;
	float textWidth = Maths::Min(GUI::CalcTextSize(displayfilename).x, 90.f);
	displayfilename = textWidth >= 90 ? displayfilename.substr(0, 12) + "..." : displayfilename;

	GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (90 - textWidth) * 0.5f, cursorPos.y + 100));


	GUI::DisplayText(displayfilename);
	GUI::EndGroup();

	Resource::IResource* resource = rm.GetResource<Resource::IResource>(file);
	if (resource)
	{
		void** item = new void* (resource);
		GUI::DragDropSource(resource->GetTypeName(), displayfilename, item);
	}
}
