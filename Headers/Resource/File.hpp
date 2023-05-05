#pragma once
#include <string>
#include <vector>

#include "dllInclude.hpp"


namespace Resource
{
	class IResource;

	class File
	{
	public:

		void SetFileData(const std::string& filepath);
		void ReloadAllResourcesInFile();
		void CreateAllResourceInFile();


		std::vector<IResource*> GetResourceList() const { return m_resourceInFile; }
		std::string GetDirecory() const { return m_directory; }
		std::string GetFileName() const { return m_filename; }
		std::string GetExtension() const { return m_extension; }
		std::string GetFilepath() const {return m_directory + '\\' + m_filename + '.' + m_extension;}

	private:

		std::vector<IResource*> m_resourceInFile;
		std::string m_directory, m_filename, m_extension;
	};
}