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
		unsigned int indexInArmature;
	};


	class PHOSENGINE_API Armature 
	{
	public:

		std::vector<Bone> skeleton;

	};
}