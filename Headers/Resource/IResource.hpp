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

		virtual void Load(const std::string& filepath) = 0;
		virtual void Bind() = 0;
		virtual void Unload() = 0;
		virtual void Save() {};

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