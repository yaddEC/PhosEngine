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
#include "Wrapper/GUI.hpp"

#include "Resource/CubeMap.hpp"

void Resource::CubeMap::Load()
{
	SetProperties(GetFilePath());
	LoadData();
}

void Resource::CubeMap::Bind()
{
	Wrapper::RHI::BindCubeMap(&m_cubeMapKey, m_datas, m_faces);
	for (int i = 0; i < 6; i++)
	{
		if(!m_faces[i]) continue;
		stbi_image_free(m_datas[i]);
	}
}

void Resource::CubeMap::Unload()
{
}

void Resource::CubeMap::Save()
{
	std::fstream progFile;
	progFile.open((p_directory + "\\" + p_name).c_str(), std::fstream::out | std::fstream::trunc);

	if (progFile)
	{
		for (size_t i = 0; i < 6; i++)
		{
			progFile << i << ' ' << (m_faces[i] ? m_faces[i]->GetFilePath() : "NULL") << '\n';
		}
	}
}

void Resource::CubeMap::GUIUpdate()
{
	using namespace Wrapper;
	std::string faceName[6] = {"Right : ", "Left :  ", "Down :  ", "Up :    ", "Front : ", "Back :  "};
	bool reload = false;
	for (size_t i = 0; i < 6; i++)
	{
		//GUI::DisplayText(faceName[i].c_str());
		if (GUI::PickTexture(faceName[i], &m_faces[i], true))
			reload = true;
		if (m_faces[i])
		{
			GUI::Image(*m_faces[i], Maths::Vec2(100, 100));
		}
		
	}
	if (reload)
	{
		std::cout << "cubemap reload" << std::endl;
		LoadData();
		Bind();
	}

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
		if (!m_faces[i]) continue;

		std::string path = m_faces[i]->GetFilePath();
		int x, y, comp;
		m_datas[i] = stbi_load(path.c_str(), &x, &y, &comp, 0);

		if(!m_datas[i])
		{
			std::cout << "Cubemap tex failed to load at path: " << m_faces[i] << std::endl;
			stbi_image_free(m_datas[i]);
		}
	}
}
