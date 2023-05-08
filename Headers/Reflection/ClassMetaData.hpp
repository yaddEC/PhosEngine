#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Engine/GameObject.hpp"
//#include "Engine/MonoBehaviour.hpp"
#include "dllInclude.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Mesh.hpp"

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
		void GUIUpdate(void* classPtr);
		std::string Save(size_t classPtr);
		void Parse(const std::vector<std::string>& tokens, size_t classPtr);
		void Copy(size_t source, size_t target);
	};


	class PHOSENGINE_API ClassMetaData
	{
	public:
		std::string name;
		std::vector<ClassMemberInfo> memberList;

		void DisplayClassInfo(void* classPtr);
		void GUIUpdate(void* classPtr);

		Resource::Texture* PosTexture = nullptr;
		Resource::Mesh* PosModelForTexture = nullptr;

		std::string Save(void* classPtr, int depth);
		void Parse(const std::vector<std::string>& fileData, size_t& lineIndex, void* classPtr);
		void Copy(void* source, void* target);

		static Engine::MonoBehaviour* AddComponent(const std::string componentName, Engine::GameObject* gameObject);
	};
}