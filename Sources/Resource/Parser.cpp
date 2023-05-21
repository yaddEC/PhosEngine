// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Resource/Parser.hpp"

std::vector<std::string> Resource::Parser::ConvertFileToStringArray(const std::string& filepath)
{
	std::vector<std::string> fileData;

	std::fstream progFile;
	progFile.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!progFile)
	{
		std::cout << "Error opening file " + filepath << std::endl;
		return fileData;
	}
	else
	{
		std::string line;
		while (std::getline(progFile, line))
		{
			fileData.push_back(line);
		}
	}

	return fileData;
}

std::vector<std::string> Resource::Parser::Tokenize(const std::string& text, char separator, char toIgnore)
{
	std::vector<std::string> result;
	std::string token;
	bool isInQuote = false;
	for (char c : text)
	{
		if (c == '\"')
		{
			isInQuote = !isInQuote;
			continue;
		}
		if (c == separator && !isInQuote)
		{
			if (!token.empty())
			{
				result.push_back(token);
				token.clear();
			}
		}
		else if (c == toIgnore)
		{
			continue;
		}
		else
		{
			token += c;
		}
	}
	if (!token.empty())
	{
		result.push_back(token);
	}
	return result;
}

Maths::Vec3 Resource::Parser::ParseVec3(std::vector<std::string> tokens, int startingToken)
{
	return Maths::Vec3(std::stof(tokens[startingToken]), std::stof(tokens[startingToken + 1]), std::stof(tokens[startingToken + 2]));
}


std::string Resource::Parser::WriteVec3(const std::string& label, const Maths::Vec3& value)
{
	return std::string();
}

Maths::Vec3 Resource::Parser::ConvertVec3(const float* vec3_ptr)
{
	return Maths::Vec3(*vec3_ptr, *(vec3_ptr + 4), *(vec3_ptr + 8));
}

Maths::Mat4 Resource::Parser::ConvertMat4(const float* mat4_ptr)
{
	Maths::Mat4 result;
	for (size_t i = 0; i < 4; i++)
	{  
		for (size_t j = 0; j < 4; j++)
		{
			result.data_4_4[i][j] = *(mat4_ptr + i * 4 + j);

		}
	}
	return result;
}
