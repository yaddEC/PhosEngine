#pragma once
#include "UIElement.hpp"


namespace Resource
{
	class Texture;
}

namespace UI
{
	class UISprite : public UIElement
	{
	public:

		class Texture* sprite;

		void Render() override;
	};
}