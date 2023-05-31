#pragma once
#include "Maths/Maths.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class Animation;
	class AnimBone;
}

namespace LowRenderer
{
	class MeshRenderer;

	class PHOSENGINE_API Animator : public Engine::MonoBehaviour
	{
	public:
		Animator();

		void Start() override;
		void Update() override;
		void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:

		void SetAnimObjects();

		std::vector<Engine::Transform*> animObjectList;
		Resource::Animation* m_currentAnimation;

		float m_timeline = 0;
		float m_speed = 1;

	};
}



