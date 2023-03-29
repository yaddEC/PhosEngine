#pragma once
#include <string>
#include "Maths/Maths.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Wrapper/GUI.hpp"

namespace EditorGUI
{
	class MenuBar
	{
	public:
		MenuBar();
		~MenuBar();

		void Update();
	};
}