// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>

#include"Wrapper/RHI.hpp"

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
	ShaderInfo vertShader;
	vertShader.source = "#version 330 core"
						"layout(location = 0) in vec2 aPos;"
						"out vec2 TexCoords;"
						"void main() { "
						"TexCoords = aPos / 2.0 + vec2(0.5, 0.5);"
						"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); }  ";
	vertShader.shaderType = GL_VERTEX_SHADER;
	m_postProShaderList.push_back(vertShader);

	std::fstream progFile;
	progFile.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!progFile)
	{
		std::cout << "Error opening file " + filepath << std::endl;
		return;
	}
	else
	{
		ShaderInfo info;
		info.shaderType = GL_FRAGMENT_SHADER;
		std::string sourceLine;
		while (getline(progFile, sourceLine))
			info.source += '\n' + sourceLine;
		m_postProShaderList.push_back(info);
	}
}

void Resource::PostProcessingShader::Bind()
{
	Wrapper::RHI::BindShader(&m_progKey, m_postProShaderList);
	p_isLoaded = true;
}

void Resource::PostProcessingShader::Unload()
{
	Wrapper::RHI::UnloadShader(&m_progKey);
}

void Resource::PostProcessingShader::Use()
{
	Wrapper::RHI::UseProgram(&m_progKey);

}
