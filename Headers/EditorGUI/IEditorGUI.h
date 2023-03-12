#pragma once
#include <string>
#include "Maths.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class IEditorGUI
{
public:
	IEditorGUI(const std::string& windowName, bool startOpen = true)
		: name(windowName), isOpen(startOpen)
	{
		Open();
	}

	void Update();
	virtual void Open() { isOpen = true; }
	virtual void Close() { isOpen = false; }
	
	Maths::Vec2 GetSize() { return size; }
	bool GetIsOnFocus() { return isOnFocus; }

	bool isOpen;

protected:
	void SetSize() { size = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y }; }
	void SetIsOnFocus() { isOnFocus = ImGui::IsWindowFocused(); }
	virtual void DoUpdate() = 0;


	std::string name;
	bool isOnFocus;
	Maths::Vec2 size;
};