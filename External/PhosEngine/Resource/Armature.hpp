#pragma once
#include "Resource/IResource.hpp"
#include <vector>
#include <string>
#include "Engine/Transform.hpp"

#include "dllInclude.hpp"



namespace Resource
{
	struct Bone
	{
		std::string name;
		Engine::Transform transform;
		unsigned int indexInArmature;
	};


	class PHOSENGINE_API Armature 
	{
	public:

		std::vector<Bone> skeleton;

	};
}