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
	class Button : public UIElement
	{
	public:

		Resource::Texture* sprite;

		void Render(const Maths::Vec2& sizeMult) override;
		void OnInspector() override;
		void Update(const Maths::Vec2& canvasPos, const Maths::Vec2& sizeMult, const Maths::Vec2& viewportSize) override;
		void Parse(std::vector<std::string> fileData, size_t& lineIndex) override;
		std::string GetTypeName() { return "Button"; }
		std::string Save() override;

		bool isPressed = false;
	};
}