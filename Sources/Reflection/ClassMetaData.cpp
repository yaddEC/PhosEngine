// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Material.hpp"
#include <iostream>
#include "Reflection/ClassMetaData.hpp"

const std::string typeToString[7] = { "int", "float", "bool", "Vec3" , "Mesh", "Material", "Material List"};

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
	case MemberType::T_INT: GUI::EditFloat(name, *(float*)(classPtr + ptr), true, 1);  break;

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
