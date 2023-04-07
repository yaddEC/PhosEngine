#pragma once
#include <string>
#include <vector>

#include "dllInclude.hpp"


namespace Reflection
{
	enum class MemberType
	{
		T_INT,
		T_FLOAT,
		T_BOOL,
		T_VEC3,
		T_MESH,
		T_MATERIAL,
		T_MATERIAL_LIST
	};


	struct PHOSENGINE_API ClassMemberInfo
	{
		ClassMemberInfo(const std::string& _name, size_t _ptr, MemberType _type)
			: name(_name), ptr(_ptr), type(_type) {}

		std::string name;
		size_t ptr;
		MemberType type;

		void DisplayMemberInfo(size_t classPtr);
		void GUIUpdate(size_t classPtr);
	};


	class PHOSENGINE_API ClassMetaData
	{
	public:
		std::string name;
		std::vector<ClassMemberInfo> memberList;

		void DisplayClassInfo(void* classPtr);
		void GUIUpdate(void* classPtr);
	};
}