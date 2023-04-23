#pragma once
#include <string>
#include "Maths/Maths.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Wrapper/GUI.hpp"

namespace Engine
{
	class Scene;
}

namespace EditorGUI
{
	class MenuBar
	{
	public:
		MenuBar();
		~MenuBar();

		void Update();

		void SetCurrentScene(Engine::Scene* currentScene) { m_currentScene = currentScene; }

	private:
		Engine::Scene* m_currentScene;

	};
}