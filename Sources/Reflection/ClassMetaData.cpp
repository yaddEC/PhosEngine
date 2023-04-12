// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "Resource/Mesh.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "Resource/Material.hpp"
#include <iostream>
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

void Reflection::ClassMemberInfo::GUIUpdate(size_t classPtr)
{
	using namespace Wrapper;

	switch (type)
	{
	case MemberType::T_INT:   break;

	case MemberType::T_FLOAT:
	{
		GUI::EditFloat(name, (float*)(classPtr + ptr), true, editSpeed, editMin, editMax);
		break;
	}

	case MemberType::T_BOOL:  break;

	case MemberType::T_VEC3: GUI::EditVec3(name, (Maths::Vec3*)(classPtr + ptr), true, editSpeed, editMin, editMax); break;

	case MemberType::T_COLOR: GUI::EditColorRGB(name, (Maths::Vec3*)(classPtr + ptr), true); break;

	case MemberType::T_MESH: 
	{
		GUI::PickMesh(name, (Resource::Mesh**)(classPtr + ptr), true);
		break;
	}
		

	case MemberType::T_MATERIAL: GUI::PickMaterial(name, (Resource::Material**)(classPtr + ptr), true); break;

	case MemberType::T_MATERIAL_LIST:
		break;

	default: break;
	}
}

std::string Reflection::ClassMemberInfo::Save(size_t classPtr, int depth)
{
	std::string result;
	result += name + ' ';

	switch (type)
	{
	case MemberType::T_INT: result += *(int*)(classPtr + ptr); break;

	case MemberType::T_FLOAT: result += *(float*)(classPtr + ptr); break;

	case MemberType::T_BOOL: result += *(bool*)(classPtr + ptr); break;

	case MemberType::T_VEC3: result += *(float*)(classPtr + ptr) + ' ' + *(float*)(classPtr + ptr + 4)
		+ ' ' + *(float*)(classPtr + ptr + 8); break;

	case MemberType::T_MESH: result += (*(Resource::Mesh**)(classPtr + ptr))->GetFilePath(); break;

	case MemberType::T_MATERIAL: result += (*(Resource::Material**)(classPtr + ptr))->GetFilePath(); break;

	case MemberType::T_MATERIAL_LIST:
		break;

	default: break;
	}
	return result + '\n';
}

void Reflection::ClassMetaData::DisplayClassInfo(void* classPtr)
{
	std::cout << "class " << name << std::endl;
	for (auto member : memberList)
	{
		std::cout << '\t';
		member.DisplayMemberInfo((size_t)classPtr);
	}
}

void Reflection::ClassMetaData::GUIUpdate(void* classPtr)
{
	if(Wrapper::GUI::CollapsingHeader(name))
	{
		for (auto member : memberList)
		{
			member.GUIUpdate((size_t)classPtr);
		}
	}
}

std::string Reflection::ClassMetaData::Save(void* classPtr, int depth)
{
	std::string result;

	for (int i = 0; i < depth; i++)
		result += 't';

	result += "comp " + name + '\n';

	for (auto member : memberList)
	{
		result += member.Save((size_t)classPtr, depth);
	}

	return result + "end\n";
}
