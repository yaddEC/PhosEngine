#pragma once
#include <string>

namespace Resource
{
	class IResource
	{
	public:

		IResource() { }

		virtual void Load(const std::string& filepath) = 0;
		virtual void Bind() = 0;
		virtual void Unload() = 0;

		inline bool GetIsLoaded() { return p_isLoaded; }

		// Do not call every frame
		virtual class Texture* GenerateFileIcon() = 0;

	protected:

		bool p_isLoaded = false;

		std::string p_directory;
		std::string p_name;
		
		void SetFileInfo(const std::string& filepath);
	};
}