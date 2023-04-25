#pragma once
#include <string>

namespace Resource
{
	struct ShaderInfo
	{
		std::string source;
		unsigned int shaderType;
		unsigned int key;
	};
}