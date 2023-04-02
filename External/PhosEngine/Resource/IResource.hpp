#pragma once
#include <string>

#ifdef IRESOURCE_EXPORTS
#define IRESOURCE_API __declspec(dllexport)
#else
#define IRESOURCE_API __declspec(dllimport)
#endif

namespace Resource
{
	class IRESOURCE_API IResource
	{
	public:

		IResource() { }
		virtual ~IResource() { }

		virtual void Load(const std::string& filepath) {}
		virtual void Bind() {}
		virtual void Unload() { p_isLoaded = false; }
		virtual void Save() {}
		virtual void GUIUpdate() {};

		virtual std::string GetTypeName() { return "IResource"; }

		inline bool GetIsLoaded() { return p_isLoaded; }
		std::string GetFilePath() { return p_directory + "\\" + p_name; }
		std::string GetName() { return p_name; }
		std::string GetDirectory() { return p_directory; }
		void SetFileInfo(const std::string& filepath);

		// Do not call every frame
		virtual class Texture* GenerateFileIcon() = 0;

	protected:

		bool p_isLoaded = false;

		std::string p_directory;
		std::string p_name;
		
	};
}