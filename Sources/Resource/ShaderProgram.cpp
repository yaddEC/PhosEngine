// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>

#include"Wrapper/RHI.hpp"

#include "Resource/ShaderProgram.hpp"

using namespace std;
using namespace Maths;
using namespace Resource;

void ShaderProgram::Load()
{

	fstream progFile;
	progFile.open(GetFilePath().c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!progFile)
	{
		cout << "Error opening file " + GetFilePath() << endl;
		return;
	}
	else
	{
		string line;
		while (getline(progFile, line))
		{
			ShaderInfo info;
			string type = line.substr(0, 4);
			if (type == "vert") info.shaderType = GL_VERTEX_SHADER;
			if (type == "frag") info.shaderType = GL_FRAGMENT_SHADER;

			string sourcePath = line.substr(5);
			info.filePath = sourcePath;
			fstream file;
			file.open(sourcePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
			if (file)
			{
				string sourceLine;
				while (getline(file, sourceLine))
					info.source += '\n' + sourceLine;
			}
			else
			{
				cout << "Error opening file " + sourcePath << endl;
				return;
			}
			m_shaderList.push_back(info);
		}
	}
	progFile.close();
}

void ShaderProgram::Bind()
{
	Wrapper::RHI::BindShader(&m_programKey, m_shaderList);
}

void ShaderProgram::Use()
{
	Wrapper::RHI::UseProgram(&m_programKey);
}

void ShaderProgram::SetUniformMatrix(const string& uniformName, const Mat4& mat) const
{
	Wrapper::RHI::ShaderMat(m_programKey, uniformName, mat);
}

void ShaderProgram::SetUniformVec3(const string& uniformName, const Vec3& vec3) const
{
	Wrapper::RHI::ShaderVec3(m_programKey, uniformName, vec3);
}

void Resource::ShaderProgram::SetUniformVec4(const std::string& uniformName, const Maths::Vec4& vec4) const
{
	Wrapper::RHI::ShaderVec4(m_programKey, uniformName, vec4);
}

void ShaderProgram::SetUniformInt(const std::string& uniformName, int value) const
{
	Wrapper::RHI::ShaderInt(m_programKey, uniformName, value);
}

void Resource::ShaderProgram::SetUniformBool(const std::string& uniformName, bool value) const
{
	Wrapper::RHI::ShaderInt(m_programKey, uniformName, (int)value);
}

void Resource::ShaderProgram::SetUniformFloat(const std::string& uniformName, float value) const
{
	Wrapper::RHI::ShaderFloat(m_programKey, uniformName, value);
}

void ShaderProgram::SetTexture(const std::string& uniformName, int value, const Texture& texture) const
{
	Wrapper::RHI::ActivateTexture(texture, value);
	Wrapper::RHI::ShaderInt(m_programKey, uniformName, value);
}

void Resource::ShaderProgram::SetCubeMap(const std::string& uniformName, int value, const CubeMap& texture) const
{
	Wrapper::RHI::ActivateCubeMap(texture, value);
	Wrapper::RHI::ShaderInt(m_programKey, uniformName, value);
}

void Resource::ShaderProgram::SetUniformMatrixArray(const std::string& uniformName, const std::vector<Maths::Mat4> matrices)
{
	for (int i = 0; i < matrices.size(); i++)
	{
		Wrapper::RHI::ShaderMatList(m_programKey, uniformName + "[0]", matrices);
	}
}

void Resource::ShaderProgram::SetUniformMatrixArray(const std::string& uniformName, const std::map<std::string, Maths::Mat4> matrices)
{
	int i = 0;
	for (auto element : matrices)
	{
		Wrapper::RHI::ShaderMat(m_programKey, uniformName + "[" + std::to_string(i) + "]", element.second);
		i++;
	}
}


void ShaderProgram::Unload()
{
	for (auto shader : m_shaderList)
	{
		Wrapper::RHI::UnloadShader(&shader.key);
	}
	m_shaderList.clear();
	Wrapper::RHI::UnloadShaderProgram(&m_programKey);
}

Texture* ShaderProgram::GenerateFileIcon()
{
	/*Texture* result = new Texture();
	unsigned char* data = new unsigned char[16]();
	unsigned char image[] = { 255, 255, 255, 255, 255, 255, 255, 0,
							 255, 255, 255, 0,  255, 255, 255, 255 };

	for (size_t i = 0; i < 16; i++)
	{
		data[i] = image[i];
	}
	result->SetData(data, 2, 2, 4);
	result->Bind();
	return result;*/
	return nullptr;
}

ShaderProgram::~ShaderProgram()
{
	Unload();
}