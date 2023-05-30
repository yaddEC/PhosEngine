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
#include "Wrapper/RHI.hpp"

void UI::SpriteRenderer::Render(const Maths::Vec2& sizeMult)
{
	if (!sprite) return;


	Resource::ShaderProgram* program = Resource::ResourceManager::GetInstance().UIShader;
	program->SetTexture("Texture", 0, *sprite);

	
	Maths::Vec2 finalScale = {-rectTransform.scale.x * sprite->GetTextureWidth() * sizeMult.x, -rectTransform.scale.y * sprite->GetTextureHeight() * sizeMult.y };

	program->SetUniformVec4("position_scale", Maths::Vec4(rectTransform.position.x,
		rectTransform.position.y,finalScale.x, finalScale.y));

	Wrapper::RHI::RenderSubMesh(Resource::ResourceManager::GetInstance().quad->GetSubMesh(0).GetVAO(),
		Resource::ResourceManager::GetInstance().quad->GetSubMesh(0).indices);
}

void UI::SpriteRenderer::OnInspector()
{
	Wrapper::GUI::PickTexture("Sprite", &sprite, true);
}

void UI::SpriteRenderer::Parse(std::vector<std::string> fileData, size_t& lineIndex)
{
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
	std::string result;
	if(sprite)
		result += "Sprite " + sprite->GetFilePath() + "\n";
	else
		result += "Sprite none\n";


	return result;
}
