// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "UI/Canvas.hpp"
#include "UI/UIElement.hpp"
#include "Wrapper/GUI.hpp"

void UI::Canvas::Load()
{

}

void UI::Canvas::Unload()
{

}

void UI::Canvas::Save()
{

}

void UI::Canvas::GUIUpdate()
{
	static UIElement* selected = nullptr;

	if (selected)
	{
		Wrapper::GUI::EditVec2("Position", selected->rectTransform.position);
	}

	for (auto element : m_uiElementList)
	{
		if(Wrapper::GUI::TreeNode(element.first, element.second == selected, true));
		if (Wrapper::GUI::IsItemClicked(0)) selected = element.second;
		Wrapper::GUI::TreePop();
	}
}

void UI::Canvas::Instantiate(UIElement* element)
{
	if (m_uiElementList.count(element->name))
	{
		element->name += " ";
	}

	int index = 1;
	while (m_uiElementList.count(element->name))
	{
		element->name.pop_back();
		element->name += std::to_string(index);
		index++;
	}

	m_uiElementList.emplace(element->name, element);
	
}
