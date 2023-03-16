#pragma once
#include <string>
#include "Maths/Maths.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GUI/GUI.hpp"

namespace EditorGUI
{
	class IEditorGUI
	{
	public:
		IEditorGUI(const std::string& windowName, bool startOpen = true)
			: name(windowName), isOpen(startOpen)
		{
		}

		void Update();

		Maths::Vec2 GetSize() { return size; }
		bool GetIsOnFocus() { return isOnFocus; }

		bool isOpen;

	protected:
		void SetSize() { size = GUI::GetWindowSize(); }
		void SetIsOnFocus() { isOnFocus = GUI::IsWondowFocused(); }
		virtual void DoUpdate() = 0;


		std::string name;
		bool isOnFocus;
		Maths::Vec2 size;
	};
}

