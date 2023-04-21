// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>

#include "Resource/Texture.hpp"

#include "Resource/PostProcessingShader.hpp"

Resource::PostProcessingShader::PostProcessingShader()
{
}

Resource::PostProcessingShader::~PostProcessingShader()
{
}

void Resource::PostProcessingShader::Load(const std::string& filepath)
{
	SetFileInfo(filepath);

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
			PostProInfo info;
			//std::string type = line.substr(0, 4);
			//if (type == "vert") info.shaderType = GL_VERTEX_SHADER;
			//if (type == "frag") info.shaderType = GL_FRAGMENT_SHADER;

			std::string sourcePath = line.substr(5);
			std::fstream file;
			file.open(sourcePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
			if (file)
			{
				std::string sourceLine;
				while (std::getline(file, sourceLine))
					info.fragSource += '\n' + sourceLine;
			}
			else
			{
				std::cout << "Error opening file " + sourcePath << std::endl;
				return;
			}
			shaderInfo = info;
		}
	}
}

void Resource::PostProcessingShader::Bind()
{

}

void Resource::PostProcessingShader::Unload()
{
}

void Resource::PostProcessingShader::Save()
{
}

void Resource::PostProcessingShader::GUIUpdate()
{

}