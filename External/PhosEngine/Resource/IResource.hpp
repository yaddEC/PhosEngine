#pragma once
#include <string>

#include "dllInclude.hpp"

namespace Resource
{
	class PHOSENGINE_API IResource
	{
	public:

		IResource() { }
		virtual ~IResource() { }

		virtual void Load() {}
		virtual void Bind() {}
		virtual void Unload() { isLoaded = false; }
		virtual void Save() {}
		virtual void GUIUpdate() {};

		virtual std::string GetTypeName() { return "IResource"; }
		
		std::string GetFilePath() { return p_directory + "\\" + p_name; }
		std::string GetName() { return p_name; }
		std::string GetDirectory() { return p_directory; }
		void SetFileInfo(const std::string& filepath);

		void SetName(const std::string& newName) { p_name = newName; }
		void SetDirectoy(const std::string& dir) { p_directory = dir; }

		// Do not call every frame
		virtual class Texture* GenerateFileIcon() { return nullptr; }

		bool isBinded = false;
		bool isLoaded = false;

	protected:


		std::string p_directory;
		std::string p_name;
		
	};
}