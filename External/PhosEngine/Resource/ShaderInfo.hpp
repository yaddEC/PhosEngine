#pragma once
#include <string>

namespace Resource
{
	struct ShaderInfo
	{
		std::string source;
		std::string filePath;
		unsigned int shaderType;
		unsigned int key;
	};
}