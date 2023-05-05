// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <fstream>
#include <iostream>

#include "Resource/ResourceIncludes.hpp"
#include"Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"

void Resource::IShader::Load()
{
	std::string filepath = GetFilePath();

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
		while (getline(progFile, line))
		{
			if (line == "#IGNORE_GENERATION")
				p_ignoreGeneration = true;
			else 
				p_sourceCode += line;
		}
	}
	progFile.close();
}

void Resource::IShader::Unload()
{
	Wrapper::RHI::UnloadShader(&p_shaderKey);
}

void Resource::IShader::GUIUpdate()
{
	Wrapper::GUI::DisplayText(p_sourceCode.c_str());
}

void Resource::VertexShader::Bind()
{
	Wrapper::RHI::BindShader(&p_shaderKey, p_sourceCode, GL_VERTEX_SHADER);
	p_isLoaded = true;
}

void Resource::FragmentShader::Bind()
{
	Wrapper::RHI::BindShader(&p_shaderKey, p_sourceCode, GL_FRAGMENT_SHADER);
	p_isLoaded = true;
}

