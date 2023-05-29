#pragma once
#include "IResource.hpp"
#include "dllInclude.hpp"

struct ma_decoder;
struct ma_device_config;
struct ma_device;

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
	private:
		ma_decoder* decoder;
		ma_device_config* deviceConfig;
		ma_device* device;
	};
}