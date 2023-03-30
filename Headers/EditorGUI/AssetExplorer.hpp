#pragma once
#include "IEditorGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>

namespace Resource
{
	class Texture;
	class IResource;
}

namespace EditorGUI
{
	class AssetExplorer : public IEditorGUI
	{
	public:
		AssetExplorer(const std::string& rootDirectory);

		~AssetExplorer();

		void Reload();

		Resource::IResource* GetSelected()
		{
			if (m_selectedClicked)
				return m_selectedResource;
			else
				return nullptr;
		}

	private:

		void DoUpdate() override;
		
		std::unordered_map<std::string, Resource::Texture*> m_fileIcons;

		const std::string m_assetsRootDirectory;
		std::string m_currentDirectory;

		void DisplayFile(const std::string& file);
		void DisplayFolder(const std::string& folder);

		std::string m_selectedFile;
		bool m_selectedClicked = false;
		Resource::IResource* m_selectedResource;

		Resource::Texture* m_defaultFileIcon, * m_folderIcon;
	};
}


