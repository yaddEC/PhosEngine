#pragma once
#include "RectTransform.hpp"
#include <string>
#include <vector>

namespace UI
{
	class UIElement
	{
	public:

		std::string name;

		RectTransform rectTransform;

		virtual void Start() {};
		virtual void Update() {};
		virtual void OnInspector() {};
		virtual void Render(const Maths::Vec2& sizeMult) {};
		virtual void OnDestroy() {};

		virtual std::string GetTypeName() = 0;
		virtual void Parse(std::vector<std::string> fileData, size_t& lineIndex) = 0;
		virtual std::string Save() = 0;

	};
}