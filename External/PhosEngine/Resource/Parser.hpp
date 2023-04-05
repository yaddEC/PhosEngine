#pragma once
#include <vector>
#include <string>

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
	};
}