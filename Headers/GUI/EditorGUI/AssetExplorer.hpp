#pragma once
#include "GUI/IGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>

#include "Resource/CubeMap.hpp"
#include "Resource/Material.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Texture.hpp"
#include "Engine/Input.hpp"

namespace Engine
{
	class Scene;
}

namespace Resource
{
	class IResource;
}

namespace EditorGUI
{
	class AssetExplorer : public APPGUI::IGUI
	{
	public:
		AssetExplorer(const std::string& rootDirectory);

		~AssetExplorer();

		void Reload();

		Resource::IResource* GetSelected() const
		{
			if (m_selectedClicked)
				return m_selectedResource;
			else
				return nullptr;
		}

		Engine::Scene* GetNewScene() const { return m_selectedScene; }

	private:

		void DoUpdate() override;
		
		std::unordered_map<std::string, Resource::Texture*> m_fileIcons;

		const std::string m_assetsRootDirectory;
		std::string m_currentDirectory;

		void DisplayFile(const std::string& file);
		void DisplayFolder(const std::string& folder);
		void NewResource();
		void CreateNewFolder(const std::string& path);
		void CreateNewFile(const std::string& path);
		void FolderButton(const std::string& folder);
		void FileButton(const std::string& file, const Maths::Vec2& cursorPos);
		void RenameFile(const std::string& file);
		void RenameFolder(const std::string& folder);

		std::string m_selectedFile;
		std::string m_copiedPath;
		bool m_selectedClicked = false;
		int m_isRenaming = -1;
		Resource::IResource* m_selectedResource;

		Engine::Scene* m_selectedScene;

		Resource::Texture* m_defaultFileIcon, * m_folderIcon;

		bool isTherePopUp ;
	};
}


