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
#include "Resource/ResourceManager.hpp"
#include "Wrapper/GUI.hpp"

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
	p_isLoaded = true;
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
		if (m_albedo.useTexture)
			progFile << "t_alb " << m_albedo.texture->GetFilePath() << '\n';
		else
			progFile << "c_alb " << m_albedo.color.x << " " << m_albedo.color.y << " " << m_albedo.color.z << '\n';

		if (m_specular.useTexture)
			progFile << "t_spec " << m_specular.texture->GetFilePath() << '\n';
		else
			progFile << "c_spec " << m_specular.color.x << " " << m_specular.color.y << " " << m_specular.color.z << '\n';

		progFile << "shiny " << m_shininess << '\n';
		progFile << "shader " << m_shader->GetFilePath() << '\n';
	}
}

void Resource::Material::GUIUpdate()
{
	Wrapper::GUI::DisplayText("Albedo");

	Wrapper::GUI::Button(m_albedo.useTexture ? m_albedo.texture->GetName() : "None");
	if (Resource::Texture** texture = (Texture**)Wrapper::GUI::DragDropTarget("Texture"))
	{
		m_albedo.texture = *texture;
		m_albedo.useTexture = true;
	}

	if (m_albedo.useTexture)
	{
		Wrapper::GUI::SameLine();
		if (Wrapper::GUI::Button("Delete"))
		{
			m_albedo.texture = nullptr;
			m_albedo.useTexture = false;
		}
	}
	else
	{
		Wrapper::GUI::EditColorRGB("##albedo", m_albedo.color);
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
			else if (prefix == "t_alb")
			{
				m_albedo.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(line.substr(6));
				m_albedo.useTexture = true;
			}
			else if (prefix == "t_spec")
			{
				m_specular.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(line.substr(7));
				m_specular.useTexture = true;
			}
			else if (prefix == "shader")
			{
				m_shader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(line.substr(7));
			}
		}
	}
}

void Resource::Material::SetProperties(const ColorMap& albedo, const ColorMap& specular, float shininess, ShaderProgram* shader)
{
	m_albedo.color = albedo.color; m_albedo.texture = albedo.texture; m_albedo.useTexture = albedo.useTexture;
	m_specular.color = specular.color; m_specular.texture = specular.texture; m_specular.useTexture = specular.useTexture;
	m_shininess = shininess;
	m_shader = shader;
}

Resource::Material Resource::Material::DefaultMaterial()
{
	Material mat;
	mat.m_albedo.color = Maths::Vec3(1, 1, 1);
	mat.m_albedo.useTexture = false;
	mat.m_specular.color = Maths::Vec3(1, 1, 1);
	mat.m_specular.useTexture = false;
	mat.m_shininess = 1;
	mat.m_shader = nullptr;

	return mat;
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
