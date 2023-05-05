// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <filesystem>
#include <time.h>

#include "Resource/File.hpp"
#include "Resource/FileManager.hpp"


typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::system_clock::duration duration;

namespace fs = std::filesystem;


void Resource::FileManager::LoadAllFiles(const std::string& _assetsRootPath)
{

	for (const auto& entry : fs::recursive_directory_iterator(_assetsRootPath))
	{
		if (!fs::is_directory(entry))
		{
			File* newFile = new File();
			newFile->SetFileData(entry.path().u8string());
			newFile->CreateAllResourceInFile();
			m_fileList.emplace(entry.path().u8string(), newFile);
		}
	}

	lastRefreshTime = std::chrono::system_clock::now().time_since_epoch();
}

void Resource::FileManager::RefreshAllFiles()
{

}

void Resource::FileManager::DeleteAllFiles()
{

}

void Resource::FileManager::GetFile(const std::string& filepath)
{
	
}
