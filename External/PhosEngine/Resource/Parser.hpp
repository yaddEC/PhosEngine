#pragma once
#include <vector>
#include <string>
#include "Maths/Maths.hpp"

#include "dllInclude.hpp"


namespace Resource
{
	class PHOSENGINE_API Parser
	{
	public:
		static std::vector<std::string> ConvertFileToStringArray(const std::string& filepath);
		static std::vector<std::string> Tokenize(const std::string& text, char separator = ' ', char toIgnore = '\0');
		static Maths::Vec3 ParseVec3(std::vector<std::string> tokens, int startingToken = 1);
		static std::string WriteVec3(const std::string& label, const Maths::Vec3& value);

		static Maths::Vec3 ConvertVec3(const float* vec3_ptr);
		static Maths::Mat4 ConvertMat4(const float* mat4_ptr);
	};
}