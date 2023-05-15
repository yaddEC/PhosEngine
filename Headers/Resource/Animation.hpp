#pragma once

#include <vector>
#include <unordered_map>
#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include "AnimBone.hpp"
#include "dllInclude.hpp"


namespace Resource
{


	class PHOSENGINE_API Animation : public IResource
	{
	public:

		void Load() override;
		void Bind() override;
		void Unload() override;
		void GUIUpdate() override;
		
		float GetDuration() const { return m_duration; }
		float GetTickRate() const { return m_tickRate; }

		std::vector<AnimBone*> GetAnimBones() const { return m_AnimBones;  }

		void DisplayBoneKeyFrame(AnimBone& current, float timeline);
		void ProcessBone(const aiAnimation* anim, const aiScene* scene);
		AnimBone* ProcessHierarchy(const aiNode* node, std::unordered_map<std::string, AnimBone*>& boneMap
			, AnimBone* parent, int& index);

		float m_duration;
		float m_tickRate;
		std::vector<AnimBone*> m_AnimBones;

	};
}