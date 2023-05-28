#pragma once
#include "UIElement.hpp"
#include <string>
#include <vector>


namespace Resource
{
	class Texture;
}

namespace UI
{
	class SpriteRenderer : public UIElement
	{
	public:

		Resource::Texture* sprite;

		void Render() override;
		void OnInspector() override;
		void Parse(std::vector<std::string> fileData, size_t& lineIndex) override;
		std::string GetTypeName() { return "SpriteRenderer"; }
		std::string Save() override;
	};
}