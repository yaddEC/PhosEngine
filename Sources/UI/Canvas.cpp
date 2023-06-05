// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "UI/Canvas.hpp"
#include "UI/UIElement.hpp"
#include "Wrapper/GUI.hpp"
#include "Resource/Parser.hpp"
#include <fstream>
#include "UI/SpriteRenderer.hpp"
#include "UI/Button.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceIncludes.hpp"




void UI::Canvas::Load()
{
	std::vector<std::string> fileData = Resource::Parser::ConvertFileToStringArray(GetFilePath());
	
	auto tokens = Resource::Parser::Tokenize(fileData[0]);
	m_baseResolution = Maths::Vec2(std::stof(tokens[0]), std::stof(tokens[1]));
	size_t lineIndex = 1;
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

	progFile << m_baseResolution.x << ' ' << m_baseResolution.y << '\n';
	for (auto element : m_uiElementList)
	{
		progFile << element.second->GetTypeName() << " \"" << element.first << "\"\n";
		progFile << "RectTransform " << element.second->rectTransform.position.x << ' ' <<
			element.second->rectTransform.position.y << ' ' << element.second->rectTransform.scale.x << ' ' << element.second->rectTransform.scale.y << '\n';
		progFile << element.second->Save() << "end\n";
	}

	progFile.close();
}

void UI::Canvas::GUIUpdate()
{
	using namespace Wrapper;

	GUI::EditVec2("Base Resolution", m_baseResolution, true);

	GUI::Separator();

	static UIElement* selected = nullptr;

	if (selected)
	{
		std::string newName = selected->name;
		if (GUI::InputString("Name", newName, true))
		{
			m_uiElementList.erase(selected->name);
			selected->name = newName;
			m_uiElementList.emplace(newName, selected);

		}
			
		GUI::EditVec2("Position", selected->rectTransform.position, true, 0.01f);
		GUI::EditVec2("Scale", selected->rectTransform.scale, true, 0.01f);
		selected->OnInspector();
		if (GUI::Button("Delete"))
		{
			m_uiElementList.erase(selected->name);
			delete selected;
			selected = nullptr;
		}
	}

	GUI::Separator();

	for (auto element : m_uiElementList)
	{
		GUI::Selectable(element.first, element.second == selected);
		if (GUI::IsItemClicked(0)) selected = element.second;
	}

	GUI::Separator();

	if (GUI::BeginPopup("New Element Popup"))
	{
		if (GUI::Selectable("Sprite", false))
		{
			auto newElement = new SpriteRenderer();
			newElement->name = "Sprite Renderer";
			Instantiate(newElement);
		}
		if (GUI::Selectable("Button", false))
		{
			auto newElement = new Button();
			newElement->name = "Button";
			Instantiate(newElement);
		}

		GUI::EndPopup();
	}

	if (GUI::Button("New Element"))
	{
		GUI::OpenPopup("New Element Popup");
	}
}

void UI::Canvas::Update(const Maths::Vec2& canvasPos, const Maths::Vec2& viewportSize)
{
	float scaling{ Maths::Lerp(viewportSize.x / m_baseResolution.x, viewportSize.y / m_baseResolution.y, 0.5f) };

	Maths::Vec2 sizeRatio = Maths::Vec2(scaling / viewportSize.x, scaling / viewportSize.y);

	for (auto element : m_uiElementList)
	{
		element.second->Update(canvasPos, sizeRatio, viewportSize);
	}
}


void UI::Canvas::Instantiate(UIElement* element)
{
	if (m_uiElementList.count(element->name))
	{
		element->name += " 1";
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

	float scaling {Maths::Lerp(viewportSize.x / m_baseResolution.x, viewportSize.y / m_baseResolution.y, 0.5f)};

	Maths::Vec2 sizeRatio = Maths::Vec2(scaling / viewportSize.x , scaling / viewportSize.y);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	for (auto element : m_uiElementList)
	{
		element.second->Render(sizeRatio);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}


void UI::Canvas::ParseUIelement(std::vector<std::string> fileData, size_t& lineIndex)
{
	UIElement* newElement = nullptr;
	std::vector<std::string> tokens = Resource::Parser::Tokenize(fileData[lineIndex], ' ', '\t');
	
	if (tokens[0] == "SpriteRenderer")
	{
		newElement = new SpriteRenderer();
		newElement->name = tokens[1];
	}
	if (tokens[0] == "Button")
	{
		newElement = new Button();
		newElement->name = tokens[1];
	}

	newElement->Parse(fileData, lineIndex);
	Instantiate(newElement);
}
