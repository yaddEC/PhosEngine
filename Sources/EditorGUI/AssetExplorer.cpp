#include "EditorGUI/AssetExplorer.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/GUI.hpp"

namespace fs = std::filesystem;
using namespace std;
using namespace EditorGUI;

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
			if (GUI::Button(entryName.substr(entryName.find_last_of('\\') + 1).c_str()))
			{
				m_currentDirectory = entryName;
				return;
			}
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
	if (m_fileIcons.count(file))
	{
		Resource::Texture* icon = m_fileIcons.at(file);
		icon->DisplayImage(120);
	}
	else
	{
		Resource::Texture* icon = rm.GetResource<Resource::Texture>("Assets\\Texture\\macron.png");
		if (icon)
		{
			icon->DisplayImage(120);
			
		}
	}
	//GUI::SetCursorPos(Maths::Vec2(0, cursorPos.y + 130));

	// TEMP
	std::string displayfilename = file;
	displayfilename = displayfilename.substr(displayfilename.find_last_of('\\') + 1);
	float textWidth = 90;
	//float textWidth = Maths::Min(GUI::CalcTextSize(displayfilename.c_str()).x, 120.f);
	displayfilename = textWidth >= 120 ? displayfilename.substr(0, 15) + "..." : displayfilename;

	//GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (120 - textWidth) * 0.5f, 0));


	GUI::DisplayText(displayfilename);
	GUI::EndGroup();
}
