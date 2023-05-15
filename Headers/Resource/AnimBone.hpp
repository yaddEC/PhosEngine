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

		void Load(const aiNodeAnim* channel);

		Maths::Mat4 GetGlobalMatrix(float animationTime, const Maths::Mat4& parentMatrix) const;

		std::string GetName() const { return m_name; }


		void SetArmatureIndex(int i) { m_ArmatureIndex = i; }
		int GetArmatureIndex() const { return m_ArmatureIndex; }

		Maths::Vec3 GetInterpolationPosition(float animationTime) const;
		Maths::Quaternion GetInterpolationRotation(float animationTime) const;
		Maths::Vec3 GetInterpolationScale(float animationTime) const;

	private:
		std::string m_name;

		int m_ArmatureIndex;


		std::vector<AnimBonePosition> m_positionList;
		std::vector<AnimBoneRotation> m_rotationList;
		std::vector<AnimBoneScale> m_scaleList;

	};
}