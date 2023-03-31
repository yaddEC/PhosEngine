#include "EditorGUI/AssetExplorer.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/IResource.hpp"
#include "Wrapper/GUI.hpp"

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
	Wrapper::GUI::DisplayText(m_currentDirectory);
	Wrapper::GUI::Separator();

	if (m_currentDirectory != m_assetsRootDirectory)
	{
		if (Wrapper::GUI::Button("..."))
		{
			m_currentDirectory = m_currentDirectory.substr(0, m_currentDirectory.find_last_of('\\'));
			return;
		}
	}

	Maths::Vec2 cursorPos = Wrapper::GUI::GetCursorPos();
	cursorPos.x = 15;
	Wrapper::GUI::SetCursorPos(cursorPos);
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
		if (cursorPos.x + 145 >= Wrapper::GUI::GetWindowSize().x)
		{
			cursorPos.x = 15;
			cursorPos.y += 145;
		}
		Wrapper::GUI::SetCursorPos(cursorPos);
	}

}


void AssetExplorer::DisplayFile(const string& file)
{
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	Maths::Vec2 cursorPos = Wrapper::GUI::GetCursorPos();

	Wrapper::GUI::SetCursorPos(cursorPos + Maths::Vec2(0, 4));


	Wrapper::GUI::BeginGroup();
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

	if (Wrapper::GUI::TruncTextBySize(displayfilename, 90))
		displayfilename += "...";
	
	Wrapper::GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - Wrapper::GUI::CalcTextSize(displayfilename).x) * 0.5f, cursorPos.y + 110));
	
	Wrapper::GUI::DisplayText(displayfilename);
	Wrapper::GUI::EndGroup();

	if (Wrapper::GUI::IsItemDoubleClicked(0))
	{
		m_selectedClicked = true;
		m_selectedFile = file;
		m_selectedResource = Resource::ResourceManager::GetInstance().GetResource<Resource::IResource>(file);
	}
	

	Resource::IResource* resource = rm.GetResource<Resource::IResource>(file);
	if (resource)
	{
		void** item = new void* (resource);
		Wrapper::GUI::DragDropSource(resource->GetTypeName(), displayfilename, item);
	}
}


void EditorGUI::AssetExplorer::DisplayFolder(const std::string& folder)
{
	Maths::Vec2 cursorPos = Wrapper::GUI::GetCursorPos();

	Wrapper::GUI::BeginGroup();

	m_folderIcon->DisplayImage(100);

	std::string displayFolderName = folder;
	displayFolderName = displayFolderName.substr(displayFolderName.find_last_of('\\') + 1);

	if (Wrapper::GUI::TruncTextBySize(displayFolderName, 90))
		displayFolderName += "...";

	Wrapper::GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - Wrapper::GUI::CalcTextSize(displayFolderName).x) * 0.5f, cursorPos.y + 110));
	Wrapper::GUI::DisplayText(displayFolderName);

	Wrapper::GUI::EndGroup();

	if(Wrapper::GUI::IsItemClicked(0))
		m_currentDirectory = folder;

}
