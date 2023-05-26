#include "GUI/EditorGUI/AssetExplorer.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/ResourceManager.hpp"
#include "Engine/GameObject.hpp"
#include "Wrapper/GUI.hpp"

#include <fstream>

namespace fs = std::filesystem;
using namespace std;
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;

static bool resource = false;

AssetExplorer::AssetExplorer(const std::string& rootDirectory)
	: IGUI("Assets", true), m_assetsRootDirectory(rootDirectory), m_currentDirectory(rootDirectory)
{

}

AssetExplorer::~AssetExplorer()
{
	for (auto icon : m_fileIcons)
	{
		if (icon.second) delete icon.second;
	}
}


string GetFileExtension(const string& filename)
{
	return filename.substr(filename.find_last_of('.') + 1);
}


void AssetExplorer::Reload()
{
	for (const auto& entry : fs::recursive_directory_iterator(m_assetsRootDirectory))
	{
		string entryName = entry.path().u8string();
		Resource::IResource* resource = Resource::ResourceManager::GetInstance().GetResource<Resource::IResource>(entryName);
		if (resource && m_fileIcons.count(entryName) == 0)
		{
			m_fileIcons.emplace(entryName, resource->GenerateFileIcon());
			//m_fileIcons.emplace(entryName, nullptr);
		}
	}

	m_folderIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\folderWhite.png");
	m_defaultFileIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\whiteFile.png");
}

void AssetExplorer::DoUpdate()
{
	Input& input = Input::GetInstance();

	GUI::DisplayText(m_currentDirectory.c_str()); GUI::SameLine();

	GUI::SetCursorPos(Maths::Vec2(GUI::GetWindowSize().x - 110, GUI::GetCursorPos().y - 5));

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
	m_selectedScene = nullptr;

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
	int selected = -1;
	const char* names[] = { "New Folder", "New File", "New Resource" };
	bool toggles[] = { true, false, false };


	GUI::TextUnformatted(selected == -1 ? "<None>" : names[selected]);
	if (input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_2) && GUI::IsWindowHovered() && !isTherePopUp)
	{
		GUI::OpenPopup("my_select_popup");
		isTherePopUp = true;
	}

	if (isTherePopUp && (input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_2) || input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)))
	{
		isTherePopUp = false;
	}

	if (GUI::BeginPopup("my_select_popup"))
	{
	
		for (int i = 0; i < IM_ARRAYSIZE(names); i++)
		{
			if (GUI::Selectable(names[i], false))
			{
				selected = i;
				switch (selected)
				{
				case 0: // New Folder
					CreateNewFolder(m_currentDirectory);
					break;
				case 1: // New File
					CreateNewFile(m_currentDirectory);
					break;
				case 2:
					resource = true;
					break;

				default:
					break;
				}

			}
		}
		GUI::EndPopup();
	}

	if (resource)
	{
		GUI::OpenPopup("New_Resource_Popup");
		resource = false;
	}
	GUI::SameLine();
	

	if (Engine::GameObject** go = (Engine::GameObject**)GUI::DragDropTarget("GameObject"))
	{
		std::fstream progFile;
		progFile.open((m_currentDirectory + "\\" + (*go)->name + ".phprefab").c_str(), std::fstream::out | std::fstream::trunc);
		Resource::Prefab* pr = Resource::ResourceManager::GetInstance().CreateResource<Resource::Prefab>(m_currentDirectory + "\\" + (*go)->name + ".phprefab");
		pr->SaveGameObjectAsPrefab(*go, progFile);
	}
}


void AssetExplorer::DisplayFile(const string& file)
{
	std::string popup_id = "file_popup_" + file;
	Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
	Maths::Vec2 cursorPos = GUI::GetCursorPos();
	Resource::IResource* resource = rm.GetResource<Resource::IResource>(file);

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
	//GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - GUI::CalcTextSize(displayfilename).x) * 0.5f, cursorPos.y + 110));


	if (m_isRenaming != -1)
	{
		if (m_isRenaming == 0)
		{
			if (displayfilename == "New File.txt")
			{
				GUI::SetNextItemWidth(100);
				GUI::SetKeyboardFocusHere();
				if (Wrapper::GUI::InputString("##RenameObject", displayfilename))
				{
					std::string newFolderPath = file.substr(0, file.find_last_of('\\')) + "\\" + displayfilename;
					if ((fs::exists(file) && !fs::exists(newFolderPath)) || displayfilename == "New File")
					{
						fs::rename(file, newFolderPath);
						m_isRenaming = -1;
					}

				}

				GUI::EndGroup();
			}
			else
			{
				FileButton(file, cursorPos);
			}

		}
		else
		{
			if (displayfilename == "New File(" + std::to_string(m_isRenaming) + ").txt")
			{
				GUI::SetNextItemWidth(100);
				GUI::SetKeyboardFocusHere();
				if (Wrapper::GUI::InputString("##RenameObject", displayfilename))
				{
					std::string newFolderPath = file.substr(0, file.find_last_of('\\')) + "\\" + displayfilename;
					if ((fs::exists(file) && !fs::exists(newFolderPath)) || displayfilename == "New File(" + std::to_string(m_isRenaming) + ").txt")
					{
						fs::rename(file, newFolderPath);
						m_isRenaming = -1;
					}

				}
				GUI::EndGroup();
			}
			else
			{
				FileButton(file, cursorPos);
			}
		}
	}
	else
	{
		FileButton(file, cursorPos);

		if (resource)
		{
			if (GUI::IsItemDown(1))
			{
				GUI::OpenPopup(popup_id);
				isTherePopUp = true;
			}
			if (GUI::IsItemDoubleClicked(0))
			{
				if (resource->GetTypeName() == "Scene")
				{
					m_selectedScene = (Engine::Scene*)resource;
				}
				else
				{
					m_selectedClicked = true;
					m_selectedFile = file;
					m_selectedResource = resource;
				}
			}
		}


		if (resource)
		{
			GUI::DragDropSource(resource->GetTypeName(), displayfilename, &resource);
		}

		Input& input = Input::GetInstance();
		int selected = -1;


		GUI::SameLine();

		if (GUI::BeginPopup(popup_id))
		{
			if (GUI::Selectable("Rename", false))
			{
				selected = 0;
				RenameFile(file);
			}
			if (GUI::Selectable("Copy", false))
			{
				selected = 1;
			}
			if (GUI::Selectable("Delete", false))
			{
				selected = 2;
				fs::remove(file);
			}
			GUI::Separator();
			if (GUI::Selectable("Reload", false))
			{
				resource->Unload();
				resource->Load();
				resource->Bind();
			}
			GUI::EndPopup();
		}
	}
}


void EditorGUI::AssetExplorer::DisplayFolder(const std::string& folder)
{
	std::string popup_id = "file_popup_" + folder;
	Maths::Vec2 cursorPos = GUI::GetCursorPos();
	GUI::BeginGroup();
	m_folderIcon->DisplayImage(100);
	std::string displayFolderName = folder;
	displayFolderName = displayFolderName.substr(displayFolderName.find_last_of('\\') + 1);
	GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - GUI::CalcTextSize(displayFolderName).x) * 0.5f, cursorPos.y + 110));

	if (m_isRenaming != -1)
	{
		if (m_isRenaming == 0)
		{
			if (displayFolderName == "New Folder")
			{
				GUI::SetNextItemWidth(100);
				GUI::SetKeyboardFocusHere();
				if (Wrapper::GUI::InputString("##RenameObject", displayFolderName))
				{
					std::string newFolderPath = folder.substr(0, folder.find_last_of('\\')) + "\\" + displayFolderName;
					if ((fs::exists(folder) && !fs::exists(newFolderPath)) || displayFolderName == "New Folder")
					{
						fs::rename(folder, newFolderPath);
						m_isRenaming = -1;
					}

				}

				GUI::EndGroup();
			}
			else
			{
				FolderButton(folder);
			}

		}
		else
		{
			if (displayFolderName == "New Folder(" + std::to_string(m_isRenaming) + ")")
			{
				GUI::SetNextItemWidth(100);
				GUI::SetKeyboardFocusHere();
				if (Wrapper::GUI::InputString("##RenameObject", displayFolderName))
				{
					std::string newFolderPath = folder.substr(0, folder.find_last_of('\\')) + "\\" + displayFolderName;
					if ((fs::exists(folder) && !fs::exists(newFolderPath)) || displayFolderName == "New Folder(" + std::to_string(m_isRenaming) + ")")
					{
						fs::rename(folder, newFolderPath);
						m_isRenaming = -1;
					}

				}
				GUI::EndGroup();
			}
			else
			{
				FolderButton(folder);
			}
		}
	}
	else
	{
		FolderButton(folder);

		if (GUI::IsItemClicked(0))
			m_currentDirectory = folder;
		if (GUI::IsItemDown(1))
		{
			GUI::OpenPopup(popup_id);
			isTherePopUp = true;
		}

		Input& input = Input::GetInstance();
		int selected = -1;
		const char* names[] = { "Rename", "Copy", "Delete" };
		bool toggles[] = { true, false, false };


		GUI::SameLine();
		GUI::TextUnformatted(selected == -1 ? "<None>" : names[selected]);

		if (GUI::BeginPopup(popup_id))
		{
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
			{
				if (GUI::Selectable(names[i], false))
				{
					selected = i;
					switch (selected)
					{
					case 0:
						RenameFolder(folder);
						break;
					case 1:
						//WIP
						break;
					case 2:
						fs::remove_all(folder);
						break;
					default:
						break;
					}
				}

			}
			GUI::EndPopup();
		}
	}


}

void EditorGUI::AssetExplorer::NewResource()
{
	if (GUI::BeginPopup("New_Resource_Popup"))
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


	
}

void EditorGUI::AssetExplorer::CreateNewFolder(const std::string& path)
{

	int index = 1;
	m_isRenaming = 0;
	std::string new_folder_name = "New Folder";
	std::string new_folder_path = path + "\\" + new_folder_name;
	while (fs::exists(new_folder_path))
	{
		new_folder_path = path + "\\" + new_folder_name + "(" + std::to_string(index) + ")";
		m_isRenaming = index;
		index++;
	}

	fs::create_directory(new_folder_path);


}

void EditorGUI::AssetExplorer::CreateNewFile(const std::string& path)
{

	int index = 1;
	m_isRenaming = 0;
	std::string new_file_name = "New File.txt";
	std::string new_file_path = path + "\\" + new_file_name;

	while (fs::exists(new_file_path))
	{
		new_file_path = path + "\\" + "New File(" + std::to_string(index) + ").txt";
		m_isRenaming = index;
		index++;
	}

	std::ofstream new_file(new_file_path);
	new_file.close();
}

void EditorGUI::AssetExplorer::FolderButton(const std::string& folder)
{
	std::string displayFolderName = folder;
	displayFolderName = displayFolderName.substr(displayFolderName.find_last_of('\\') + 1);

	if (GUI::TruncTextBySize(displayFolderName, 90))
		displayFolderName += "...";


	GUI::DisplayText(displayFolderName.c_str());
	//GUI::SameLine();

	GUI::EndGroup();
}

void EditorGUI::AssetExplorer::FileButton(const std::string& file, const Maths::Vec2& cursorPos)
{
	std::string displayfilename = file;
	displayfilename = displayfilename.substr(displayfilename.find_last_of('\\') + 1);

	if (GUI::TruncTextBySize(displayfilename, 90))
		displayfilename += "...";

	GUI::SetCursorPos(Maths::Vec2(cursorPos.x + (100 - GUI::CalcTextSize(displayfilename).x) * 0.5f, cursorPos.y + 110));

	GUI::DisplayText(displayfilename.c_str());
	GUI::EndGroup();
}

void EditorGUI::AssetExplorer::RenameFile(const std::string& file)
{
	int index = 1;
	m_isRenaming = 0;
	std::string new_file_name = "New File.txt";
	std::string path = file.substr(0, file.find_last_of('\\'));
	std::string new_file_path = path + "\\" + new_file_name;

	while (fs::exists(new_file_path))
	{
		new_file_path = path + "\\" + "New File(" + std::to_string(index) + ").txt";
		m_isRenaming = index;
		index++;
	}

	fs::rename(file, new_file_path);
}

void EditorGUI::AssetExplorer::RenameFolder(const std::string& folder)
{
	int index = 1;
	m_isRenaming = 0;
	std::string new_folder_name = "New Folder";
	std::string path = folder.substr(0, folder.find_last_of('\\'));
	std::string new_folder_path = path + "\\" + new_folder_name;
	while (fs::exists(new_folder_path))
	{
		new_folder_path = path + "\\" + new_folder_name + "(" + std::to_string(index) + ")";
		m_isRenaming = index;
		index++;
	}

	fs::rename(folder, new_folder_path);

}
