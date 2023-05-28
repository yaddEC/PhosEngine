// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "UI/SpriteRenderer.hpp"
#include "Resource/Parser.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Wrapper/GUI.hpp"
#include "Resource/ResourceIncludes.hpp"


void UI::SpriteRenderer::Render()
{
	Resource::ShaderProgram* program = Resource::ResourceManager::GetInstance().UIShader;
	if(sprite)
		program->SetTexture("Texture", 0, *sprite);
}

void UI::SpriteRenderer::OnInspector()
{
	Wrapper::GUI::PickTexture("Sprite", &sprite, true);
}

void UI::SpriteRenderer::Parse(std::vector<std::string> fileData, size_t& lineIndex)
{
	name = "Sprite Renderer";
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Resource::Parser::Tokenize(fileData[lineIndex], ' ', '\t');

		if (tokens[0] == "RectTransform")
		{
			rectTransform.position = Maths::Vec2(std::stof(tokens[1]), std::stof(tokens[2]));
			rectTransform.scale = Maths::Vec2(std::stof(tokens[3]), std::stof(tokens[4]));
		}
		if (tokens[0] == "Sprite")
		{
			sprite = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(tokens[1]);
		}
		if (tokens[0] == "end")
		{
			lineIndex++;
			return;
		}
	}
}

std::string UI::SpriteRenderer::Save()
{
	return "Sprite " + sprite->GetFilePath() + "\n";
}
