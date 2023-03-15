// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SHADERPROGRAM_EXPORTS
#include "Resource/ShaderProgram.hpp"

using namespace std;
using namespace Maths;
using namespace Resource;

void ShaderProgram::Load(const std::string& filepath)
{
	SetFileInfo(filepath);

	fstream progFile;
	progFile.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!progFile)
	{
		cout << "Error opening file " + filepath << endl;
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

			string sourcePath = p_directory + '\\' + line.substr(5);
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
}

void ShaderProgram::Bind()
{
	m_programKey = glCreateProgram();

	for (auto& shader : m_shaderList)
	{
		shader.key = GetCompiledShader(shader.shaderType, shader.source);
		if (shader.key == -1)
		{
			cout << "Error binding shader" << endl;
			return;
		}
	}

	for (auto& shader : m_shaderList)
	{
		glAttachShader(m_programKey, shader.key);
	}

	glLinkProgram(m_programKey);

	int success;
	glGetProgramiv(m_programKey, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_programKey, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	for (auto& shader : m_shaderList)
	{
		glDeleteShader(shader.key);
	}

}

int ShaderProgram::GetCompiledShader(unsigned int shaderType, const std::string& shaderSource)
{
	//compile shader
	unsigned int shaderID = glCreateShader(shaderType);

	const char* source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);


	// check if shader compilation succeded
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = new char[length];
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		delete[] infoLog;

		return -1;
	}

	return shaderID;
}

void ShaderProgram::Use() const
{
	glUseProgram(m_programKey);
}

void ShaderProgram::SetUniformMatrix(const string& uniformName, const Mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_programKey, uniformName.c_str()), 1, true, &mat.data_4_4[0][0]);
}

void ShaderProgram::SetUniformVec3(const string& uniformName, const Vec3& vec3) const
{
	glUniform3fv(glGetUniformLocation(m_programKey, uniformName.c_str()), 1, &vec3.x);
}

void ShaderProgram::SetUniformInt(const std::string& uniformName, int value) const
{
	glUniform1i(glGetUniformLocation(m_programKey, uniformName.c_str()), value);
}

void ShaderProgram::Unload()
{
	glDeleteProgram(m_programKey);
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