#pragma once
#include <vector>
#include <string>
#include "Maths/Maths.hpp"

#ifdef PARSER_EXPORTS
#define PARSER_API __declspec(dllexport)
#else
#define PARSER_API __declspec(dllimport)
#endif


namespace Resource
{
	class PARSER_API Parser
	{
	public:
		static std::vector<std::string> ConvertFileToStringArray(const std::string& filepath);
		static std::vector<std::string> Tokenize(const std::string& text, char separator = ' ', char toIgnore = '\0');
		static Maths::Vec3 ParseVec3(std::vector<std::string> tokens, int startingToken = 1);
		static std::string WriteVec3(const std::string& label, const Maths::Vec3& value);
	};
}