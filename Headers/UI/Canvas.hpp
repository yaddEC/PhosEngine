#pragma once
#include "Resource/IResource.hpp"
#include <map>


namespace Resource
{
	class Texture;
}

namespace UI
{
	class UIElement;

	class Canvas : public Resource::IResource
	{
	public:

		void Load() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;

		void Instantiate(UIElement* element);

	private:

		std::map<std::string, UIElement*> m_uiElementList;
	};
}