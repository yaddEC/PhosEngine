#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "dllInclude.hpp"


namespace Reflection
{
	enum class MemberType
	{
		T_INT,
		T_FLOAT,
		T_BOOL,
		T_VEC3,
		T_COLOR,
		T_MESH,
		T_MATERIAL,
		T_MATERIAL_LIST
	};


	struct PHOSENGINE_API ClassMemberInfo
	{
		ClassMemberInfo(const std::string& _name, size_t _ptr, MemberType _type, float _editSpeed = 0.1f, float _min = 0, float _max = 0)
			: name(_name), ptr(_ptr), type(_type), editSpeed(_editSpeed), editMin(_min), editMax(_max) {}

		std::string name;
		size_t ptr;
		MemberType type;

		float editSpeed;
		float editMin;
		float editMax;

		void DisplayMemberInfo(size_t classPtr);
		void GUIUpdate(size_t classPtr);
		std::string Save(size_t classPtr, int depth);
	};


	class PHOSENGINE_API ClassMetaData
	{
	public:
		std::string name;
		std::vector<ClassMemberInfo> memberList;

		void DisplayClassInfo(void* classPtr);
		void GUIUpdate(void* classPtr);

		std::string Save(void* classPtr, int depth);
		void Parse(const std::vector<std::string>& fileData, size_t& lineIndex);
	};
}