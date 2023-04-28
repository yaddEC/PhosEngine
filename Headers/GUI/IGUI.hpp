#pragma once
#include <string>
#include "Maths/Maths.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Wrapper/GUI.hpp"

namespace APPGUI
{
	class IGUI
	{
	public:
		IGUI(const std::string& windowName, bool startOpen = true)
			: p_name(windowName), isOpen(startOpen)
		{
		}

		void Update();

		Maths::Vec2 GetSize() { return p_size; }
		bool GetIsOnFocus() { return p_isOnFocus; }

		bool isOpen;

	protected:
		void SetSize() { p_size = Wrapper::GUI::GetWindowSize(); }
		void SetIsOnFocus() { p_isOnFocus = Wrapper::GUI::IsWondowFocused(); }
		virtual void DoUpdate() = 0;


		std::string p_name;
		bool p_isOnFocus;
		Maths::Vec2 p_size;
	};
}

