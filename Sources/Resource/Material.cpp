// include needed
#include <utility>
#include <limits>
#include "pch.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Resource/Texture.hpp"
#include "Resource/ShaderProgram.hpp"

#define MATERIAL_EXPORTS
#include "Resource/Material.hpp"

namespace fs = std::filesystem;

void Resource::Material::Load(const std::string& filepath)
{
	SetFileInfo(filepath);
	SetProperties(filepath);
}

void Resource::Material::Bind()
{

}

void Resource::Material::Unload()
{

}

void Resource::Material::Save()
{
	std::fstream progFile;
	progFile.open((p_directory + "\\" + p_name).c_str(), std::fstream::out | std::fstream::trunc);

	if (progFile)
	{
		progFile << "c_alb " << m_albedo.color.x << " " << m_albedo.color.y << " " << m_albedo.color.z << '\n';
		progFile << "c_spec " << m_specular.color.x << " " << m_specular.color.y << " " << m_specular.color.z << '\n';
		progFile << "shiny " << m_shininess;
	}
}

Resource::Texture* Resource::Material::GenerateFileIcon()
{
	return nullptr;
}

void Resource::Material::SendDataToShader() const
{
	if (m_albedo.useTexture)
		m_shader->SetTexture("material.albedo.texture", 0, *m_albedo.texture);
	else
		m_shader->SetUniformVec3("material.albedo.color", m_albedo.color);
	m_shader->SetUniformBool("material.albedo.useTexture", m_albedo.useTexture);


	if (m_specular.useTexture)
		m_shader->SetTexture("material.specular.texture", 1, *m_specular.texture);
	else
		m_shader->SetUniformVec3("material.specular.color", m_specular.color);
	m_shader->SetUniformBool("material.specular.useTexture", m_specular.useTexture);

	m_shader->SetUniformFloat("material.shininess", m_shininess);
}

void Resource::Material::SetProperties(const std::string& filepath)
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
			size_t offset = line.find(' ');
			std::string prefix = line.substr(0, offset);

			if (prefix == "c_alb")
			{
				std::vector<std::string> values = split(line.substr(offset + 1).c_str(), ' ');

				m_albedo.color = Maths::Vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]));
				m_albedo.useTexture = false;
			}
			else if (prefix == "c_spec")
			{
				std::vector<std::string> values = split(line.substr(offset + 1).c_str(), ' ');

				m_specular.color = Maths::Vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]));
				m_specular.useTexture = false;
			}
			else if (prefix == "shiny")
			{
				std::string sh = line.substr(offset);

				m_shininess = std::stof(sh) ;
				
			}
		}
	}
}

std::vector<std::string> Resource::Material::split(const char* str, char c)
{
	std::vector<std::string> result;
	do
	{
		const char* begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}
