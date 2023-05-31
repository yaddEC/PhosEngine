#pragma once
#include "IResource.hpp"
#include "dllInclude.hpp"

struct ma_sound;

namespace Resource
{
	class PHOSENGINE_API Audio : public IResource
	{
	public:
		Audio();
		~Audio();
		void Create();
		void Play(bool isLooping);
		void Stop();
		void SetVolume(float value);
		float GetVolume();
	private:
		ma_sound* sound;
	};
}