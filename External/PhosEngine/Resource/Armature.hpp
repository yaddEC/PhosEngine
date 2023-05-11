#pragma once
#include "Resource/IResource.hpp"
#include <vector>
#include <string>
#include "Engine/Transform.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "dllInclude.hpp"



namespace Resource
{
	struct Bone
	{
		std::string name;
		Maths::Mat4 inverseBind;

		std::vector<Bone*> children;

		unsigned int GetArmatureIndex() const { return armatureIndex; }
		void SetArmatureIndex(unsigned int i) { armatureIndex = i; }

	private:
		unsigned int armatureIndex;
	};


	class PHOSENGINE_API Armature 
	{
	public:

		std::vector<Bone> boneMap;

	};
}