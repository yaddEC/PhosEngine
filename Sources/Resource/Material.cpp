// include needed
#include <utility>
#include <limits>
#include "pch.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Resource/Parser.hpp"
#include "Wrapper/GUI.hpp"

#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"

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

		if(m_shader)
			progFile << "shader " << m_shader->GetFilePath() << '\n';

		if (m_normalMap)
			progFile << "t_norm " << m_normalMap->GetFilePath() << '\n';

		if (m_metallic.useTexture)
			progFile << "t_meta " << m_metallic.texture->GetFilePath() << '\n';
		else
			progFile << "v_meta " << m_metallic.value << '\n';

		if (m_roughness.useTexture)
			progFile << "t_rough " << m_roughness.texture->GetFilePath() << '\n';
		else
			progFile << "v_rough " << m_roughness.value << '\n';
	}
}

void Resource::Material::GUIUpdate()
{
	std::string shaderName = m_shader ? m_shader->GetName() : "No Shader";
	if (GUI::Combo("Shader : ", ResourceManager::GetInstance().GetResourceNameList<ShaderProgram>(), shaderName))
	{
		m_shader = ResourceManager::GetInstance().GetResource<ShaderProgram>(shaderName);
	}

	m_albedo.GUIUpdate("Albedo : ");
	m_roughness.GUIUpdate("Roughness : ");
	m_metallic.GUIUpdate("Metallic : ");

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


	if (m_normalMap)
	{
		m_shader->SetTexture("material.normalMap.texture", 2, *m_normalMap);
		m_shader->SetUniformBool("material.normalMap.useTexture", true);
	}
	else
	{
		m_shader->SetUniformVec3("material.normalMap.color", Maths::Vec3(0.5f, 0.5f, 1));
		m_shader->SetUniformBool("material.normalMap.useTexture", false);
	}


	if (m_roughness.useTexture)
		m_shader->SetTexture("material.roughness.texture", 3, *m_roughness.texture);
	else
		m_shader->SetUniformVec3("material.roughness.color", Maths::Vec3(m_roughness.value, 0, 0));
	m_shader->SetUniformBool("material.roughness.useTexture", m_roughness.useTexture);


	if (m_metallic.useTexture)
		m_shader->SetTexture("material.metallic.texture", 4, *m_metallic.texture);
	else
		m_shader->SetUniformVec3("material.metallic.color", Maths::Vec3(m_metallic.value, 0, 0));
	m_shader->SetUniformBool("material.metallic.useTexture", m_metallic.useTexture);
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
			std::vector<std::string> tokens = Parser::Tokenize(line, ' ');

			if (tokens[0] == "c_alb")
			{
				m_albedo.color = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
				m_albedo.useTexture = false;
			}
			else if (tokens[0] == "t_alb")
			{
				m_albedo.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(tokens[1]);
				m_albedo.useTexture = true;
			}
			else if (tokens[0] == "shader")
			{
				m_shader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(tokens[1]);
			}
			else if (tokens[0] == "t_norm")
			{
				m_normalMap = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(tokens[1]);
			}
			else if (tokens[0] == "t_meta")
			{
				m_metallic.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(tokens[1]);
				m_metallic.useTexture = true;
			}
			else if (tokens[0] == "v_meta")
			{
				m_metallic.value = std::stof(tokens[1]);
			}
			else if (tokens[0] == "t_rough")
			{
				m_roughness.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(tokens[1]);
				m_roughness.useTexture = true;
			}
			else if (tokens[0] == "v_rough")
			{
				m_roughness.value = std::stof(tokens[1]);
			}
		}
	}
}

void Resource::Material::SetProperties(const ColorMap& albedo, const ColorMap& specular, float shininess, ShaderProgram* shader)
{
	m_albedo.color = albedo.color; m_albedo.texture = albedo.texture; m_albedo.useTexture = albedo.useTexture;
	m_shader = shader;
}

Resource::Material Resource::Material::DefaultMaterial()
{
	Material mat;
	mat.m_albedo.color = Maths::Vec3(1, 1, 1);
	mat.m_albedo.useTexture = false;

	mat.m_shader = nullptr;

	mat.m_normalMap = nullptr;

	mat.m_roughness.value = 0.5f;
	mat.m_roughness.useTexture = false;

	mat.m_metallic.value = 0.f;
	mat.m_metallic.useTexture = false;

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

void Resource::ValueMap::GUIUpdate(const std::string& label)
{
	GUI::BeginGroup();


	std::string selectedSpec = useTexture ? texture->GetName() : "Value";
	if (GUI::Combo(label, Resource::ResourceManager::GetInstance().GetResourceNameList<Texture>(), selectedSpec, true, "Value"))
	{
		if (selectedSpec == "Value")
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
		GUI::EditFloat("value" + label, value, false, 0.001f, 0.f, 1.0f);
}
