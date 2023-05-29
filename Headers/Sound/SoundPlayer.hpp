#pragma once

#include "Engine/MonoBehaviour.hpp"
#include "Resource/Audio.hpp"
#include "dllInclude.hpp"

namespace Sound
{
	class PHOSENGINE_API SoundPlayer : public Engine::MonoBehaviour
	{
	public:
		SoundPlayer();
		~SoundPlayer();

		Resource::Audio* audio;

		void Update() override;
		void Start() override;
		void OnInspector() override;
		void GUIUpdate() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;
	protected :
		std::string selected;
		bool p_isLooping;
	};
}