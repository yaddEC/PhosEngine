#include "EditorGUI/AssetExplorer.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/IResource.hpp"
#include "Resource/CubeMap.hpp"
#include "Wrapper/GUI.hpp"

#include <fstream>

namespace fs = std::filesystem;
using namespace std;
using namespace Wrapper;
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

	m_folderIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\folderWhite.png");
	m_defaultFileIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\whiteFile.png");
}

void AssetExplorer::DoUpdate()
{
	GUI::DisplayText(m_currentDirectory); GUI::SameLine();

	GUI::SetCursorPos(Maths::Vec2(GUI::GetWindowSize().x - 95, GUI::GetCursorPos().y - 5));

	NewResource();

	GUI::Separator();

	if (m_currentDirectory != m_assetsRootDirectory)
	{
		if (GUI::Button("..."))
		{
			m_currentDirectory = m_currentDirectory.substr(0, m_currentDirectory.find_last_of('\\'));
			return;
		}
	}

	Maths::Vec2 cursorPos = GUI::GetCursorPos();
	cursorPos.x = 15;
	GUI::SetCursorPos(cursorPos);
	m_selectedClicked = false;

	for (const auto& entry : fs::directory_iterator(m_currentDirectory))
	{
		string entryName = entry.path().u8string();

		if (fs::is_directory(entry))
		{
			DisplayFolder(entry.path().u8string());
		}
		else
		{
			DisplayFile(entry.path().u8string());
		}

		cursorPos.x += 145;
		if (cursorPos.x + 145 >= GUI::GetWindowSize().x)
		{
			cursorPos.x = 15;
			cursorPos.y += 145;
		}
		GUI::SetCursorPos(cursorPos);
	}


	

}


void AssetExplorer::DisplayFile(const string& file)
{
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	Maths::Vec2 cursorPos = GUI::GetCursorPos();

	GUI::SetCursorPos(cursorPos + Maths::Vec2(0, 4));


	GUI::BeginGroup();
	if (m_fileIcons.count(file) && m_fileIcons.at(file))
	{
		Resource::Texture* icon = m_fileIcons.at(file);
		icon->DisplayImage(100);
	}
	else
	{
		m_defaultFileIcon->DisplayImage(100);
	}

	std::string displayfilename = file;
	displayfilename = displayfilename.substr(displayfilename.find_last_of('\\') + 1);

	if (GUI::TruncTextBySize(displayfilename, 90))
		displayfilename += "...";
	
	GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - GUI::CalcTextSize(displayfilename).x) * 0.5f, cursorPos.y + 110));
	
	GUI::DisplayText(displayfilename);
	GUI::EndGroup();

	if (GUI::IsItemDoubleClicked(0))
	{
		m_selectedClicked = true;
		m_selectedFile = file;
		m_selectedResource = Resource::ResourceManager::GetInstance().GetResource<Resource::IResource>(file);
	}
	

	Resource::IResource* resource = rm.GetResource<Resource::IResource>(file);
	if (resource)
	{
		void** item = new void* (resource);
		GUI::DragDropSource(resource->GetTypeName(), displayfilename, item);
	}
}


void EditorGUI::AssetExplorer::DisplayFolder(const std::string& folder)
{
	Maths::Vec2 cursorPos = GUI::GetCursorPos();

	GUI::BeginGroup();

	m_folderIcon->DisplayImage(100);

	std::string displayFolderName = folder;
	displayFolderName = displayFolderName.substr(displayFolderName.find_last_of('\\') + 1);

	if (GUI::TruncTextBySize(displayFolderName, 90))
		displayFolderName += "...";

	GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - GUI::CalcTextSize(displayFolderName).x) * 0.5f, cursorPos.y + 110));
	GUI::DisplayText(displayFolderName);

	GUI::EndGroup();

	if(GUI::IsItemClicked(0))
		m_currentDirectory = folder;

}

void EditorGUI::AssetExplorer::NewResource()
{
	if (GUI::BeginPopupContextItem("New Resource Popup"))
	{
		if (GUI::Selectable("Cube Map", false))
		{
			std::fstream progFile;
			progFile.open((m_currentDirectory + "\\" + "NewCubeMap.phcm").c_str(), std::fstream::out | std::fstream::trunc);
			Resource::CubeMap* cm = Resource::ResourceManager::GetInstance().CreateResource<Resource::CubeMap>(m_currentDirectory + "\\" + "NewCubeMap.phcm");
			cm->Save();
		}
		if (GUI::Selectable("Material", false))
		{

		}

		GUI::EndPopup();
	}

	if (GUI::Button("New Resource"))
	{
		GUI::OpenPopup("New Resource Popup");
	}
}
