#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace Engine
{
	class PHOSENGINE_API Input
	{
	public:

		Input(const Input&) = delete;

		static Input& GetInstance()
		{
			static Input instance;
			return instance;
		}

		void Update();

		void Init(GLFWwindow* _window);

		float GetHorizontalAxis();
		float GetVerticalAxis();

		bool IsKeyPressed(int key);
		bool IsKeyDown(int key);
		bool IsAnyKeyDown();

		bool IsMouseButtonPressed(int mouseButton);

		Maths::Vec2 GetMouseDelta();

	private:
		Input() {}

		GLFWwindow* window;
		Maths::Vec2 mousePosition;
		Maths::Vec2 mouseDelta;

		int keyMap[348];
		bool anyKeyDown;

		void DisplayGUI();

	};
}

