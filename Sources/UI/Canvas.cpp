// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "UI/Canvas.hpp"
#include "UI/UIElement.hpp"
#include "Wrapper/GUI.hpp"
#include "Resource/Parser.hpp"
#include <fstream>
#include "UI/SpriteRenderer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"

void UI::Canvas::Load()
{
	std::vector<std::string> fileData = Resource::Parser::ConvertFileToStringArray(GetFilePath());
	
	size_t lineIndex = 0;
	while (lineIndex < fileData.size() - 1)
	{
		ParseUIelement(fileData, lineIndex);
	}
}

void UI::Canvas::Unload()
{

}

void UI::Canvas::Save()
{
	std::fstream progFile;
	progFile.open((p_directory + "\\" + p_name).c_str(), std::fstream::out | std::fstream::trunc);

	for (auto element : m_uiElementList)
	{
		progFile << element.second->GetTypeName() << " \"" << element.first << "\"\n";
		progFile << "RectTransform " << element.second->rectTransform.position.x << ' ' <<
			element.second->rectTransform.position.y << ' ' << element.second->rectTransform.scale.x << ' ' << element.second->rectTransform.scale.y;
		progFile << element.second->Save() << "end";
	}

	progFile.close();
}

void UI::Canvas::GUIUpdate()
{
	static UIElement* selected = nullptr;

	if (selected)
	{
		Wrapper::GUI::EditVec2("Position", selected->rectTransform.position, true, 0.01f);
		Wrapper::GUI::EditVec2("Scale", selected->rectTransform.scale, true, 0.01f);
		selected->OnInspector();
	}

	Wrapper::GUI::Separator();

	for (auto element : m_uiElementList)
	{
		Wrapper::GUI::Selectable(element.first, element.second == selected);
		if (Wrapper::GUI::IsItemClicked(0)) selected = element.second;
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

void UI::Canvas::RenderUI(const Maths::Vec2& viewportSize) const
{
	Resource::ShaderProgram* program = Resource::ResourceManager::GetInstance().UIShader;

	program->Use();

	for (auto element : m_uiElementList)
	{
		program->SetUniformVec4("position_scale", Maths::Vec4(element.second->rectTransform.position.x,
			element.second->rectTransform.position.y, element.second->rectTransform.scale.x, element.second->rectTransform.scale.y));

		element.second->Render();
	}
}


void UI::Canvas::ParseUIelement(std::vector<std::string> fileData, size_t& lineIndex)
{
	UIElement* newElement = nullptr;
	std::vector<std::string> tokens = Resource::Parser::Tokenize(fileData[lineIndex], ' ', '\t');
	
	if (tokens[0] == "SpriteRenderer")
	{
		newElement = new SpriteRenderer();
	}

	newElement->Parse(fileData, lineIndex);
	Instantiate(newElement);
}
