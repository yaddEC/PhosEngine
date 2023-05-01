#pragma once
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include "dllInclude.hpp"

namespace Resource
{
	struct AnimBonePosition
	{
		Maths::Vec3 position;
		float timeStamp;
	};

	struct AnimBoneRotation
	{
		Maths::Quaternion rotation;
		float timeStamp;
	};

	struct AnimBoneScale
	{
		Maths::Vec3 scale;
		float timeStamp;
	};

	class AnimBone
	{
	public:

		void Load(const std::string& name, int ID, const aiNodeAnim* channel);

		void UpdateTransform(float animationTime);

	private:

		Maths::Vec3 GetInterpolationPosition(float animationTime) const;
		Maths::Quaternion GetInterpolationRotation(float animationTime) const;
		Maths::Vec3 GetInterpolationScale(float animationTime) const;

		std::string m_name;
		Maths::Mat4 m_localMatrix;
		int m_parentID;

		std::vector<AnimBonePosition> m_positionList;
		std::vector<AnimBoneRotation> m_rotationList;
		std::vector<AnimBoneScale> m_scaleList;

	};
}