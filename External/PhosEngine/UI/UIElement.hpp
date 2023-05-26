#pragma once
#include "RectTransform.hpp"
#include <string>

namespace UI
{
	class UIElement
	{
	public:

		std::string name;

		RectTransform rectTransform;

		virtual void Start() {};
		virtual void Update() {};
		virtual void Render() {};
		virtual void OnDestroy() {};

	};
}