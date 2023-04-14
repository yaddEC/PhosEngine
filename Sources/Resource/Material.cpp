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
#include "Resource/Parser.hpp"
#include "Wrapper/GUI.hpp"

#define MATERIAL_EXPORTS
#include "Resource/Material.hpp"

using namespace Wrapper;

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
		if (m_normalMap)
			progFile << "t_norm " << m_normalMap->GetFilePath() << '\n';
	}
}

void Resource::Material::GUIUpdate()
{
	std::string shaderName = m_shader->GetName();
	if (GUI::Combo("Shader : ", ResourceManager::GetInstance().GetResourceNameList<ShaderProgram>(), shaderName))
	{
		m_shader = ResourceManager::GetInstance().GetResource<ShaderProgram>(shaderName);
	}

	m_albedo.GUIUpdate("Albedo : ");
	m_specular.GUIUpdate("Specular : ");

	std::string normalMap = m_normalMap ? m_normalMap->GetName() : "None";;
	if (GUI::Combo("Normal map : ", ResourceManager::GetInstance().GetResourceNameList<Texture>(), normalMap, true, "None"))
	{
		if (normalMap == "None")
		{
			m_normalMap = nullptr;
		}
		else
		{
			m_normalMap = ResourceManager::GetInstance().GetResource<Texture>(normalMap);
		}
	}

	GUI::EditFloat("Shininess : ", m_shininess, true, 0.01f, 0, 64);

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

	if (m_normalMap)
	{
		m_shader->SetTexture("material.normalMap.texture", 2, *m_normalMap);
		m_shader->SetUniformBool("material.normalMap.useTexture", true);
	}
	else
	{
		m_shader->SetUniformVec3("material.normalMap.color", Maths::Vec3(0, 0, 1));
		m_shader->SetUniformBool("material.normalMap.useTexture", false);
	}
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
				std::vector<std::string> values = Parser::Tokenize(line.substr(offset + 1).c_str(), ' ');

				m_albedo.color = Maths::Vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2]));
				m_albedo.useTexture = false;
			}
			else if (prefix == "c_spec")
			{
				std::vector<std::string> values = Parser::Tokenize(line.substr(offset + 1).c_str(), ' ');

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
			else if (prefix == "t_norm")
			{
				m_normalMap = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(line.substr(7));
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


void Resource::ColorMap::GUIUpdate(const std::string& label)
{

	GUI::BeginGroup();


	std::string selectedSpec = useTexture ? texture->GetName() : "Color";
	if (GUI::Combo(label, Resource::ResourceManager::GetInstance().GetResourceNameList<Texture>(), selectedSpec, true, "Color"))
	{
		if (selectedSpec == "Color")
		{
			texture = nullptr;
			useTexture = false;
		}
		else
		{
			texture = ResourceManager::GetInstance().GetResource<Texture>(selectedSpec);
			useTexture = true;
		}
	}

	GUI::EndGroup();

	if (Resource::Texture** newtexture = (Texture**)Wrapper::GUI::DragDropTarget("Texture"))
	{
		texture = *newtexture;
		useTexture = true;
	}
	if (!useTexture)
		GUI::EditColorRGB(label, color, false);
}