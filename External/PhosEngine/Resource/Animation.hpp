#pragma once

#include <vector>
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

	class PHOSENGINE_API Animation : public IResource
	{
	public:

		/*void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;*/

	private:

		float m_duration;
		float m_tickRate;
		std::vector<AnimBonePosition> m_bonesPosition;
		std::vector<AnimBoneRotation> m_bonesRotation;
		std::vector<AnimBoneScale> m_bonesScale;

	};
}