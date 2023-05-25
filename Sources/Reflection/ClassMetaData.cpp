// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/CameraComponent.hpp"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "Resource/ResourceIncludes.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Parser.hpp"
#include <iostream>
#include "LowRenderer/Animator.hpp"
#include "Reflection/ClassMetaData.hpp"

const std::string typeToString[] = { "int", "float", "bool", "Vec3", "Color", "Mesh", "Material", "Material List"};

void Reflection::ClassMemberInfo::DisplayMemberInfo(size_t classPtr)
{
	std::cout << typeToString[(int)type] << ' ' << name << " = ";

	switch (type)
	{
	case MemberType::T_INT: std::cout << *(int*)(classPtr + ptr) << std::endl; break;

	case MemberType::T_FLOAT: std::cout << *(float*)(classPtr + ptr) << std::endl; break;

	case MemberType::T_BOOL: std::cout << *(bool*)(classPtr + ptr) << std::endl; break;

	case MemberType::T_VEC3: std::cout << *(float*)(classPtr + ptr) << ", " << *(float*)(classPtr + ptr + 4)
		<< ", " << *(float*)(classPtr + ptr + 8) << std::endl; break;

	case MemberType::T_MESH: std::cout << (*(Resource::Mesh**)(classPtr + ptr))->GetFilePath() << std::endl; break;

	case MemberType::T_MATERIAL: std::cout << (*(Resource::Material**)(classPtr + ptr))->GetFilePath() << std::endl; break;

	case MemberType::T_MATERIAL_LIST:
		std::cout << "{ ";
		for (Resource::Material mat : (*(std::vector<Resource::Material>*)(classPtr + ptr)))
		{
			std::cout << mat.GetName() << " ";
		}
		std::cout << " }";
		break;

	default: break;
	}
}

void Reflection::ClassMemberInfo::GUIUpdate(void* classPtr)
{
	using namespace Wrapper;
	//component->GUIUpdate();
	Engine::MonoBehaviour* monoBehavior = static_cast<Engine::MonoBehaviour*>(classPtr);
	switch (type)
	{
	case MemberType::T_INT:   break;

	case MemberType::T_FLOAT:
	{
		
		if (GUI::EditFloat(name, (float*)((size_t)classPtr + ptr), true, editSpeed, editMin, editMax))
		{
			monoBehavior->GUIUpdate();
		}
		
		break;
	}

	case MemberType::T_BOOL:  
	{
		GUI::DisplayText(name.c_str());
		GUI::SameLine();
		if (GUI::CheckBox(name, (bool*)((size_t)classPtr + ptr), true))
		{
			monoBehavior->GUIUpdate();
		}
		break;
	}

	case MemberType::T_VEC3:
	{
		if (GUI::EditVec3(name, (Maths::Vec3*)((size_t)classPtr + ptr), true, editSpeed, editMin, editMax))
		{
			monoBehavior->GUIUpdate();
		}
		 break;
	}
	case MemberType::T_COLOR:
	{
		if (GUI::EditColorRGB(name, (Maths::Vec3*)((size_t)classPtr + ptr), true))
		{
			monoBehavior->GUIUpdate();
		}
		
		
		break;
	}

	case MemberType::T_MESH: 
	{
		if (GUI::PickMesh(name, (Resource::Mesh**)((size_t)classPtr + ptr), true))
		{
			monoBehavior->GUIUpdate();
		}
		
		break;
	}
		

	case MemberType::T_MATERIAL:
	{
		if (GUI::PickMaterial(name, (Resource::Material**)((size_t)classPtr + ptr), true))
		{
			monoBehavior->GUIUpdate();
		}
		 break;
	}

	case MemberType::T_MATERIAL_LIST:
		break;

	case MemberType::T_POSTPROCESSINGSHADER:
		if (GUI::PickPostProcessing(name, (Resource::PostProcessingShader**)((size_t)classPtr + ptr), true))
		{
			monoBehavior->GUIUpdate();
		}
		break;

	default: break;
	}
}

std::string Reflection::ClassMemberInfo::Save(size_t classPtr)
{
	std::string result;
	result += name + ' ';

	switch (type)
	{
	case MemberType::T_INT: result += std::to_string(*(int*)(classPtr + ptr)); break;

	case MemberType::T_FLOAT: result += std::to_string(*(float*)(classPtr + ptr)); break;

	case MemberType::T_BOOL: result += std::to_string(*(bool*)(classPtr + ptr)); break;

	case MemberType::T_VEC3: result += std::to_string(*(float*)(classPtr + ptr))
		+ ' ' + std::to_string(*(float*)(classPtr + ptr + 4))
		+ ' ' + std::to_string(*(float*)(classPtr + ptr + 8)); break;

	case MemberType::T_COLOR: result += std::to_string(*(float*)(classPtr + ptr))
		+ ' ' + std::to_string(*(float*)(classPtr + ptr + 4))
		+ ' ' + std::to_string(*(float*)(classPtr + ptr + 8)); break;

	case MemberType::T_MESH: 
		result += (*(Resource::Mesh**)(classPtr + ptr)) ? (*(Resource::Mesh**)(classPtr + ptr))->GetFilePath() : "None"; break;

	case MemberType::T_MATERIAL:
		result += (*(Resource::Material**)(classPtr + ptr)) ? (*(Resource::Material**)(classPtr + ptr))->GetFilePath() : "None"; break;

	case MemberType::T_MATERIAL_LIST:
		break;

	case MemberType::T_POSTPROCESSINGSHADER:
		result += (*(Resource::PostProcessingShader**)(classPtr + ptr)) ? (*(Resource::PostProcessingShader**)(classPtr + ptr))->GetFilePath() : "None"; break;

	default: break;
	}
	return result + '\n';
}

void Reflection::ClassMemberInfo::Parse(const std::vector<std::string>& tokens, size_t classPtr)
{
	switch (type)
	{
	case MemberType::T_INT: *(int*)(classPtr + ptr) = std::stoi(tokens[1]); break;

	case MemberType::T_FLOAT: *(float*)(classPtr + ptr) = std::stof(tokens[1]);  break;

	case MemberType::T_BOOL:*(bool*)(classPtr + ptr) = std::stoi(tokens[1]); break;

	case MemberType::T_VEC3: *(float*)(classPtr + ptr) = std::stof(tokens[1]);
		*(float*)(classPtr + ptr + 4) = std::stof(tokens[2]);
		*(float*)(classPtr + ptr + 8) = std::stof(tokens[3]); break;

	case MemberType::T_COLOR: *(float*)(classPtr + ptr) = std::stof(tokens[1]);
		*(float*)(classPtr + ptr + 4) = std::stof(tokens[2]);
		*(float*)(classPtr + ptr + 8) = std::stof(tokens[3]); break;

	case MemberType::T_MESH: (*(Resource::Mesh**)(classPtr + ptr))
		= Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(tokens[1]); break;

	case MemberType::T_MATERIAL: (*(Resource::Material**)(classPtr + ptr))
		= Resource::ResourceManager::GetInstance().GetResource<Resource::Material>(tokens[1]); break;

	case MemberType::T_MATERIAL_LIST:
		break;

	case MemberType::T_POSTPROCESSINGSHADER: (*(Resource::PostProcessingShader**)(classPtr + ptr))
		= Resource::ResourceManager::GetInstance().GetResource<Resource::PostProcessingShader>(tokens[1]); break;

	default: break;
	}
}

void Reflection::ClassMemberInfo::Copy(size_t source, size_t target)
{
	switch (type)
	{
	case MemberType::T_INT: *(int*)(target + ptr) = *(int*)(source + ptr); break;

	case MemberType::T_FLOAT: *(float*)(target + ptr) = *(float*)(source + ptr);  break;

	case MemberType::T_BOOL: *(bool*)(target + ptr) = *(bool*)(source + ptr); break;

	case MemberType::T_VEC3: *(Maths::Vec3*)(target + ptr) = *(Maths::Vec3*)(source + ptr); break;

	case MemberType::T_MESH: *(Resource::Mesh**)(target + ptr) = *(Resource::Mesh**)(source + ptr); break;

	case MemberType::T_MATERIAL: *(Resource::Material**)(target + ptr) = *(Resource::Material**)(source + ptr); break;

	case MemberType::T_MATERIAL_LIST: break;

	case MemberType::T_POSTPROCESSINGSHADER: *(Resource::PostProcessingShader**)(target + ptr) = *(Resource::PostProcessingShader**)(source + ptr); break;

	default: break;
	}
}

void Reflection::ClassMetaData::DisplayClassInfo(void* classPtr)
{
	std::cout << "class " << name << std::endl;
	for (auto member : memberList)
	{
		member.DisplayMemberInfo((size_t)classPtr);
	}
}

void Reflection::ClassMetaData::GUIUpdate(void* classPtr)
{
	if(Wrapper::GUI::CollapsingHeader(name))
	{
		for (auto member : memberList)
		{
			member.GUIUpdate(classPtr);
		}
	}
}

std::string Reflection::ClassMetaData::Save(void* classPtr, int depth)
{
	std::string result;
	std::string tab = std::string(depth - 1, '\t');

	result += tab;
	result += "component \"" + name + "\"\n";

	for (auto member : memberList)
	{
		result += tab + '\t';
		result += member.Save((size_t)classPtr);
	}
	result += tab + '\t';
	return result + "end\n";
}

void Reflection::ClassMetaData::Parse(const std::vector<std::string>& fileData, size_t& lineIndex, void* classPtr)
{
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Resource::Parser::Tokenize(fileData[lineIndex], ' ', '\t');

		if (tokens[0] == "end")
			return;

		for (auto member : memberList)
		{
			if (member.name == tokens[0])
			{
				member.Parse(tokens, (size_t)classPtr);
			}
		}
	}
}

void Reflection::ClassMetaData::Copy(void* source, void* target)
{
	for (auto member : memberList)
	{
		member.Copy((size_t)source, (size_t)target);
	}
}

Engine::MonoBehaviour* Reflection::ClassMetaData::AddComponent(const std::string componentName, Engine::GameObject* gameObject)
{
	if (componentName == "Mesh Renderer")
	{
		return gameObject->AddComponent<LowRenderer::MeshRenderer>();
	}
	if (componentName == "Point Light")
	{
		return gameObject->AddComponent<LowRenderer::PointLight>();
	}
	if (componentName == "Spot Light")
	{
		return gameObject->AddComponent<LowRenderer::SpotLight>();
	}
	if (componentName == "Directional Light")
	{
		return gameObject->AddComponent<LowRenderer::DirectionalLight>();
	}
	if (componentName == "RigidBody")
	{
		return gameObject->AddComponent<Physic::Rigidbody>();
	}
	if (componentName == "Box Collider")
	{
		return gameObject->AddComponent<Physic::BoxCollider>();
	}
	if (componentName == "Sphere Collider")
	{
		return gameObject->AddComponent<Physic::SphereCollider>();
	}
	if (componentName == "Capsule Collider")
	{
		return gameObject->AddComponent<Physic::CapsuleCollider>();
	}
	if (componentName == "Animator")
	{
		return gameObject->AddComponent<LowRenderer::Animator>();
	}
	if (componentName == "Camera Component")
	{
		return gameObject->AddComponent<LowRenderer::CameraComponent>();
	}

	return nullptr;
}
