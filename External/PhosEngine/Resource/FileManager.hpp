#pragma once

#include <unordered_map>
#include <time.h>
#include <string>
#include <chrono>
#include <filesystem>


namespace Resource
{
	class File;

	class FileManager
	{
	public:

		static FileManager& GetInstance()
		{
			static FileManager instance;
			return instance;
		}

		void LoadAllFiles(const std::string& _assetsRootPath);
		void RefreshAllFiles();
		// call only at application end.
		void DeleteAllFiles();
		void GetFile(const std::string& filepath);


	private:

		FileManager();
		
		std::string assetsRootPath;
		std::unordered_map<std::string, File*> m_fileList;

		
		std::chrono::system_clock::duration lastRefreshTime;
	};
}
