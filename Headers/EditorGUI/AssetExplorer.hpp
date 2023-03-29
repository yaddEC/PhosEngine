#pragma once
#include "IEditorGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>

namespace Resource
{
	class Texture;
}

namespace EditorGUI
{
	class AssetExplorer : public IEditorGUI
	{
	public:
		AssetExplorer(const std::string& rootDirectory);

		~AssetExplorer();

		void Reload();

	private:

		void DoUpdate() override;
		std::unordered_map<std::string, Resource::Texture*> m_fileIcons;

		const std::string m_assetsRootDirectory;
		std::string m_currentDirectory;

		void DisplayFile(const std::string& file);
	};
}


