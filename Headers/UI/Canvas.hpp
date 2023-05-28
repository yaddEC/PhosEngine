#pragma once
#include "Resource/IResource.hpp"
#include <vector>
#include <map>
#include "Maths/Maths.hpp"


namespace Resource
{
	class Texture;
}

namespace UI
{
	class UIElement;

	class PHOSENGINE_API Canvas : public Resource::IResource
	{
	public:

		void Load() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		std::string GetTypeName() override { return "Canvas"; }

		void Instantiate(UIElement* element);

		void RenderUI(const Maths::Vec2& viewportSize) const;

	private:

		void ParseUIelement(std::vector<std::string> fileData, size_t& lineIndex);

		std::map<std::string, UIElement*> m_uiElementList;
	};
}