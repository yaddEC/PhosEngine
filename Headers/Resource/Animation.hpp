#pragma once

#include <vector>
#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include "AnimBone.hpp"
#include "dllInclude.hpp"


namespace Resource
{


	class PHOSENGINE_API Animation : public IResource
	{
	public:

		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;

		
		std::vector<AnimBone> GetAnimBones() const { return m_AnimBones;  }

	private:

		float m_duration;
		float m_tickRate;
		std::vector<AnimBone> m_AnimBones;

	};
}