#pragma once
#include "Maths/Maths.hpp"


namespace UI
{
	enum class AnchorPoint
	{
		AP_TOPLEFT,
		AP_TOPRIGHT,
		AP_BOTTOMLEFT,
		AP_BOTTOMRIGHT,
		AP_CENTER
	};

	class RectTransform
	{
	public:

		Maths::Vec2 position;
		Maths::Vec2 scale;
		AnchorPoint anchor;
	};
}