// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <STB_Image/stb_image.h>

#include "Wrapper/RHI.hpp"

#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

#define CUBEMAP_EXPORTS
#include "Resource/CubeMap.hpp"

void Resource::CubeMap::Load(const std::string& filepath)
{
	SetFileInfo(filepath);
	SetProperties(filepath);
	LoadData();
}

void Resource::CubeMap::Bind()
{
	Wrapper::RHI::BindCubeMap(m_cubeMapKey, m_datas, m_faces);
	for (int i = 0; i < 6; i++)
	{
		stbi_image_free(m_datas[i]);
	}
}

void Resource::CubeMap::Unload()
{
}

Resource::Texture* Resource::CubeMap::GenerateFileIcon()
{
	return nullptr;
}

void Resource::CubeMap::SetProperties(const std::string& filepath)
{
	std::fstream progFile;
	progFile.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!progFile)
	{
		std::cout << "Error opening file " + filepath << std::endl;
		return;
	}
	else
	{
		std::string line;
		while (std::getline(progFile, line))
		{
			int faceIndex = (int)line[0] - '0';
			std::string texturePath = line.substr(2);
			m_faces[faceIndex] = Resource::ResourceManager::GetInstance().GetResource <Resource::Texture>(texturePath);
		}
	}
}

void Resource::CubeMap::LoadData()
{
	for (int i = 0; i < 6; i++)
	{
		std::string path = m_faces[i]->GetFilePath();
		m_datas[i] = stbi_load(path.c_str(), nullptr, nullptr, nullptr, 0);

		if(!m_datas[i])
		{
			std::cout << "Cubemap tex failed to load at path: " << m_faces[i] << std::endl;
			stbi_image_free(m_datas[i]);
		}
	}
}
